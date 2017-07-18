//
// Created by Jury Verrigni on 18/07/2017.
//

#include "Mcp3008.h"
#ifdef WATERBOT_RASPI
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif


void Mcp3008::Init(WaterBotConfig* Config)
{
#ifdef WATERBOT_RASPI
    SpiChannel = Config::ReadCustomField("Mcp3008", "SpiChannel", 0);
    loadSpiDriver();
    wiringPiSetup();
    spiSetup(SpiChannel);
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
