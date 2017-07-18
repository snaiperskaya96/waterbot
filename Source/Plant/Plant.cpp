 /** 
 *  WaterBot
 *  
 *  Created by Jury Verrigni at SkayaHack.com
 */

#include <Http/Http.h>
#include <AnalogInterface/AnalogInterface.h>
#include "Plant.h"
#ifdef WATERBOT_RASPI
#include <wiringPi.h>
#endif

Plant::Plant(std::string Name, int Pin)
{
    this->Name = Name;
    this->Pin = Pin;
#ifdef WATERBOT_RASPI
    pinMode (Pin, INPUT) ;
#endif
}

Plant::~Plant() {}

std::string Plant::GetName()
{
    return this->Name;
}

void Plant::Update()
{
    int HumidityValue = AnalogInterface::GetInstance().AnalogRead(Pin);
    HumidityPercentage = 100 - (100 * HumidityValue / 1024);
    Http::GetInstance().UpdatePlant(this);
}

double Plant::GetHumidityPercentage()
{
    return HumidityPercentage;
}

