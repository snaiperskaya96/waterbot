/** 
 *  WaterBot
 *  
 *  Created by Jury Verrigni at SkayaHack.com
 */

#ifndef Plant_h
#define Plant_h

#include <string>

class Plant {
  private:
    std::string Name;
    int Pin;
    double HumidityPercentage;
    
  public:
    Plant(std::string Name, int Pin);
    ~Plant();
    void Update();
    std::string GetName();
    double GetHumidityPercentage();
};

#endif
