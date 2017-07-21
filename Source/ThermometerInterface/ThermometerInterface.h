//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_THERMOMETERINTERFACE_H
#define WATERBOT_THERMOMETERINTERFACE_H


#include <Config/Config.h>
#include <DeviceInterface/DeviceInterface.h>
#include <thread>
#include "ThermometerDeviceInterface.h"

class ThermometerInterface : public DeviceInterface<ThermometerInterface> {
public:
    void Update() override;
private:
    std::thread UpdateThread;
    void Init() override;
private:
    int Pin;
    ThermometerDeviceInterface* Interface;
};


#endif //WATERBOT_THERMOMETERINTERFACE_H
