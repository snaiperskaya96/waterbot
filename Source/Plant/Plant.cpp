 /** 
 *  WaterBot
 *  
 *  Created by Jury Verrigni at SkayaHack.com
 */

#include <Http/Http.h>
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
#ifdef WATERBOT_RASPI
    int HumidityValue = analogRead(Pin);
#else
    int HumidityValue = 512;
#endif
    HumidityPercentage = 100 - (100 * HumidityValue / 1024);
    Http::GetInstance().UpdatePlant(this);
}

double Plant::GetHumidityPercentage()
{
    return HumidityPercentage;
}

