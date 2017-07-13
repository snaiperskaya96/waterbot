//
// Created by Jury Verrigni on 12/07/2017.
//

#ifndef WATERBOT_WATERBOT_H
#define WATERBOT_WATERBOT_H

#define WATERBOT_VERSION "0.0.1"

#ifdef WATERBOT_DEBUG
#define WDEBUG(...) printf(__VA_ARGS__)
#else
#define WDEBUG(...)
#endif

#include <Plant/Plant.h>
#include <vector>
#include <Config/Config.h>

void Loop(WaterBotConfig Conf);
void Delay(int Milis);
void RegisterPlants(WaterBotConfig Conf);
int main(int ArgC, char** ArgV);
void Daemonise();

#endif //WATERBOT_WATERBOT_H
