//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_THERMOMETERDEVICEINTERFACE_H
#define WATERBOT_THERMOMETERDEVICEINTERFACE_H

class ThermometerDeviceInterface
{
public:
    virtual void Update() = 0;
    virtual void Init() = 0;
};

#endif //WATERBOT_THERMOMETERDEVICEINTERFACE_H
