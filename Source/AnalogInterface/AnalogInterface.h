//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_ANALOGINTERFACE_H
#define WATERBOT_ANALOGINTERFACE_H


#include <Config/Config.h>
#include <DeviceInterface/DeviceInterface.h>
#include "AnalogDeviceInterface.h"

class AnalogInterface : public DeviceInterface<AnalogInterface>
{
public:
    int AnalogRead(int Pin);

private:
    void Init() override;

private:
    AnalogDeviceInterface* Interface;

};


#endif //WATERBOT_ANALOGINTERFACE_H
