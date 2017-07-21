//
// Created by Jury Verrigni on 18/07/2017.
//

#include "Dht22.h"
#include <Config/Config.h>
#include <Utils/Utils.h>

#ifdef WATERBOT_RASPI
#include <wiringPi.h>
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
        int LowSignalCounter = 0;
        int HighSignalCounter = 0;
        int ReceivedData[40];

        pullUpDnControl(4, PUD_UP);

        pinMode(4, OUTPUT);

        digitalWrite(4, LOW);
        delay(1);


        pinMode(4, INPUT);

        // Count how many cpu cycles it takes to change status
        // Keeping in mind that the first two responses from the
        // sensor take up to 80us each

        // pullup is on so ignore the first segnal we find
        // Ideally we want to add a timeout here so we don't
        // get stuck in any loop
        while (digitalRead(4) == HIGH) {}
        while (digitalRead(4) == LOW) LowSignalCounter++;
        while (digitalRead(4) == HIGH) HighSignalCounter++;

        for (int i = 0; i < 40; i++) {
            int c = 0;
            while (digitalRead(4) == LOW) {}
            while (digitalRead(4) == HIGH) c++;
            ReceivedData[i] = c;
        }

        int AverageTimeFor80us = (LowSignalCounter + HighSignalCounter) / 2;
        int AverageTimeFor50us = AverageTimeFor80us * 50 / 80;
        std::string BinaryString; // 0001000111100 ...

        for (int i =0; i < 40; i++) {
            if (ReceivedData[i] < AverageTimeFor50us) BinaryString += "0";
            else BinaryString += "1";
        }

        double Humidity = stoi(BinaryString.substr(0, 16), 0, 2) / 10;
        double Temperature = stoi(BinaryString.substr(16, 16), 0, 2) / 10;
#endif
        Utils::SetDefaultPriority();
    }
}
