//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_ANALOGINTERFACE_H
#define WATERBOT_ANALOGINTERFACE_H


#include <Config/Config.h>
#include "AnalogDeviceInterface.h"

class AnalogInterface
{
public:
    static AnalogInterface& GetInstance()
    {
        static AnalogInterface Instance;
        return Instance;
    }
    AnalogInterface(AnalogInterface const&) = delete;
    void operator=(AnalogInterface const&) = delete;

    void SetConfig(WaterBotConfig* Config)
    {
        this->Config = Config;
        this->Init();
    }

    int AnalogRead(int Pin);
private:
    void Init();
private:
    WaterBotConfig* Config;
    AnalogDeviceInterface* Interface;
private:
    AnalogInterface() {};
};


#endif //WATERBOT_ANALOGINTERFACE_H
