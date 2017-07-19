//
// Created by Jury Verrigni on 18/07/2017.
//

#include "Dht22.h"
#include <Log/loguru.h>
#include <Config/Config.h>
#include <Utils/Utils.h>
#include <thread>

#ifdef WATERBOT_RASPI
#include <wiringPi.h>
#include <WaterBot.h>
#endif

void Dht22::Update()
{

}

void Dht22::Init()
{
    LastUpdate = seconds::zero();
    ShouldStop = false;
    Pin = Config::ReadCustomIntegerField("Dht22", "Pin", 4);
    UpdateThread = std::thread(&Dht22::RetrieveData, this);
}

/**
 * https://cdn-shop.adafruit.com/datasheets/Digital+humidity+and+temperature+sensor+AM2302.pdf
 * What happens here is that when we send a start signal the DHT22 will respond back with a
 * 40 bit signal that reflects the actual humidity and temperature
 */
void Dht22::RetrieveData()
{
    const struct timespec OneSecond = {1, 0};
    while (!ShouldStop) {
        if ((duration_cast<seconds>(system_clock::now().time_since_epoch()) - LastUpdate).count() < 60) {
            nanosleep(&OneSecond, NULL);
            continue;
        }

        Utils::SetMaxPriority();
#ifdef WATERBOT_RASPI
        pinMode(Pin, OUTPUT);
        digitalWrite(Pin, HIGH);
        MiliSleep(2000);

        // Reset all the previous data
        for (int I = 0; I < 5; I++) SensorData[I] = 0;

        // Wake up the sensor
        digitalWrite(Pin, LOW);
        MiliSleep(1);

        // "Handshake" - Host pulls up for ~20-30us
        digitalWrite(Pin, LOW);
        Microsleep(30);

        // "Handshake" - Sensor pulls down for ~80us
        pinMode(Pin, INPUT);
        pullUpDnControl(Pin, PUD_UP);
        WaitForSignalChange(HIGH, 100);
        if (!ExpectSignal(LOW, 80)) {
            LOG_F(ERROR, "DHT22 - Handshake: Sensor didn't pull down for 80us");
            LastUpdate = duration_cast<seconds>(system_clock::now().time_since_epoch());
            continue;
        }
        WaitForSignalChange(LOW, 100);
        if (!ExpectSignal(HIGH, 80)) {
            LOG_F(ERROR, "DHT22 - Handshake: Sensor didn't pull up for 80us");
            LastUpdate = duration_cast<seconds>(system_clock::now().time_since_epoch());
            continue;
        }

        // Now the sensor will start sending the data for a total of 40 bits.
        // The sensor will send a LOW voltage signal that lasts ~50 us and then
        // a HIGH voltage signal that represents the sent bit.
        // If the length of the HIGH pulse is ~28 us then the value is 0 otherwise
        // if it's ~70 us is 1. Every trasmission is
        int8_t Data[40];

        for (int I = 0; I < 40; I++) {
            ExpectSignal(LOW, 50);
            int Counter = 0;
            while(ExpectSignal(HIGH, 10)) {
                Counter ++;
                if (Counter > 10) {
                    LOG_F(ERROR, "DHT22 - The sensor has been sending pulling up for more than 100us");
                    ShouldStop = true;
                    break;
                }
            }
            // If HIGH for 30 us or less then 0 else 1
            Data[I] = Counter <= 3 ? 0x00 : 0x01;
            printf("%c", Data[I]);
        }
#endif
        Utils::SetDefaultPriority();
    }
}

bool Dht22::ExpectSignal(int Type, int MicroSeconds)
{
#if WATERBOT_RASPI
    for (int I = 0; I < MicroSeconds; I++) {
        if (digitalRead(Pin) != Type) {
            WDEBUG("Dht22::ExpectSignal Failed after %d tries. Expecting %s\n", I + 1, Type == 0 ? "LOW" : "HIGH");
            return false;
        }
        Microsleep(1);
    }
#endif
    return true;
}

void Dht22::WaitForSignalChange(int CurrentType, int Timeout)
{
#if WATERBOT_RASPI
    for (int I = 0; I < Timeout; I++) {
        if (digitalRead(Pin) != CurrentType) {
            WDEBUG("Dht22::WaitForSignalChange Signal changed after %d useconds \n", I + 1);
            return;
        }
        Microsleep(1);
    }
    WDEBUG("Dht22::WaitForSignalChange timeout \n");
    return;
#endif
}

// us
void Dht22::Microsleep(int MicroSeconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(MicroSeconds));
}

// ms
void Dht22::MiliSleep(int NanoSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(NanoSeconds));
}
