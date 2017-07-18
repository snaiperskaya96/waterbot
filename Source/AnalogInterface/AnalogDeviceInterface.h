//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_ANALOGDEVICEINTERFACE_H
#define WATERBOT_ANALOGDEVICEINTERFACE_H

#include <Config/Config.h>

class AnalogDeviceInterface {
public:
    virtual void Init(WaterBotConfig* Config) = 0;
    virtual int AnalogRead(int Pin) = 0;
};

#endif //WATERBOT_ANALOGDEVICEINTERFACE_H
