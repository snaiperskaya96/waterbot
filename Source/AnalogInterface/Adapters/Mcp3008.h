//
// Created by Jury Verrigni on 18/07/2017.
//

#ifndef WATERBOT_MCP3008_H
#define WATERBOT_MCP3008_H

#include <AnalogInterface/AnalogDeviceInterface.h>

class Mcp3008 : public AnalogDeviceInterface {
public:
    void Init(WaterBotConfig* Config) override;
    int AnalogRead(int Pin) override;
private:
    int SpiChannel;
};


#endif //WATERBOT_MCP3008_H
