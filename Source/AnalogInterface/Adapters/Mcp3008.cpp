//
// Created by Jury Verrigni on 18/07/2017.
//

#include "Mcp3008.h"
#ifdef WATERBOT_RASPI
#include <Config/Config.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif


void Mcp3008::Init(WaterBotConfig* Config)
{
    SpiChannel = Config::ReadCustomIntegerField("Mcp3008", "SpiChannel", 0);
#ifdef WATERBOT_RASPI
    wiringPiSetup();
    wiringPiSPISetup(SpiChannel, 1000000);
#endif
}

int Mcp3008::AnalogRead(int Pin)
{
#ifdef WATERBOT_RASPI
    if(Pin < 0 || Pin > 7) return -1;
    unsigned char Buffer[3] = {1};
    Buffer[1] = (8 + Pin) << 4;
    wiringPiSPIDataRW(SpiChannel, Buffer, 3);
    return ( (Buffer[1] & 3 ) << 8 ) + Buffer[2];
#else
    return 512;
#endif
}
