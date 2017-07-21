//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_DEVICE_H
#define WATERBOT_DEVICE_H

#include <Config/Config.h>

/**
 * Parent class for Singleton devices
 */
template <typename T>
class DeviceInterface
{
public:
    static T & GetInstance()
    {
        static T Instance;
        return Instance;
    }
protected:
    virtual ~DeviceInterface() {}
    inline explicit DeviceInterface() {}
public:
    void SetConfig(WaterBotConfig* Configuration)
    {
        Config = Configuration;
        Init();
    }

    virtual void Update() {};
private:
    virtual void Init() {};
protected:
    WaterBotConfig* Config;
};
#endif //WATERBOT_DEVICE_H
