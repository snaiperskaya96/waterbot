//
// Created by Jury Verrigni on 12/07/2017.
//

#ifndef WATERBOT_RASPI_CONFIG_H
#define WATERBOT_RASPI_CONFIG_H

#include <string>
#include <vector>
#include "Plant/Plant.h"

struct WaterBotConfig {
public:
    WaterBotConfig(
            std::string Host,
            std::string ApiKey,
            std::string UniqueName,
            std::vector<Plant> Plants
    ) : WATERBOT_HOST(Host), WATERBOT_API_KEY(ApiKey), WATERBOT_UNIQUE_NAME(UniqueName), WATERBOT_PLANTS(Plants) {}

    const std::vector<Plant>& GetPlants() const {
        return WATERBOT_PLANTS;
    }

    const std::string& GetHost() const {
        return WATERBOT_HOST;
    }

    const std::string& GetApiKey() const {
        return WATERBOT_API_KEY;
    }

    const std::string& GetUniqueName() const {
        return WATERBOT_UNIQUE_NAME;
    }

private:
    std::string WATERBOT_HOST;
    std::string WATERBOT_API_KEY;
    std::string WATERBOT_UNIQUE_NAME;
    std::vector<Plant> WATERBOT_PLANTS;
};

class Config {
public:
    static WaterBotConfig ReadConfig(std::string Path);
    static void GenerateConfigFile(std::string FilePath);
};

#define WATERBOT_CONFIG_FILE \
"[General]\n"\
"BotName=Raspi\n"\
"Host=;https://mywaterbot.com/\n"\
"ApiKey=;Generated from waterbot-web\n"\
"NumberOfPlants=1\n"\
"\n"\
";For each plant we will have a sequential group of\n"\
";settings Plant_1, Plant_2, Plant_3...\n"\
"\n"\
"[Plant_1]\n"\
"Name=Plant1\n"\
"HumidityPin=11\n"

#endif //WATERBOT_RASPI_CONFIG_H
