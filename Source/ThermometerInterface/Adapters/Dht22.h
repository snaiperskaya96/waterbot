//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_DHT22_H
#define WATERBOT_DHT22_H


#include <ThermometerInterface/ThermometerDeviceInterface.h>
#include <cstdint>
#include <chrono>
#include <thread>

/*
 * Due to the slowness of the DHT22
 * this class will start a thread
 * that will constantly read it in
 * order to make the process free
 * from sync blocks
 */

using namespace std::chrono;

class Dht22 : public ThermometerDeviceInterface {
private:
    seconds LastUpdate;
    char SensorData[5];
    bool ShouldStop;
    int Pin;
    double Humidity;
    double Temperature;
    std::thread UpdateThread;
public:
    void Update() override;

    void Init() override;

private:
    void RetrieveData();
    void Microsleep(int MicroSeconds);

    void MiliSleep(int NanoSeconds);
};


#endif //WATERBOT_DHT22_H
