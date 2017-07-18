//
// Created by Jury Verrigni on 12/07/2017.
//

#ifndef WATERBOT_RASPI_CONFIG_H
#define WATERBOT_RASPI_CONFIG_H

#include <string>
#include <vector>
#include "Plant/Plant.h"
#include <Utils/Ini/INIReader.h>
#include <typeinfo>

static std::string ConfigPath;

struct WaterBotConfig {
public:
    WaterBotConfig(
            std::string Host,
            std::string ApiKey,
            std::string UniqueName,
            std::vector<Plant> Plants,
            int DaemonLogVerbosity,
            std::string AnalogInterface
    ) : WATERBOT_HOST(Host), WATERBOT_API_KEY(ApiKey),
        WATERBOT_UNIQUE_NAME(UniqueName), WATERBOT_PLANTS(Plants),
        DAEMON_LOG_VERBOSITY(DaemonLogVerbosity), A_INTERFACE(AnalogInterface) {}

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

    const int GetDaemonLogVerbosity() const {
        return DAEMON_LOG_VERBOSITY;
    }

    const std::string& GetAnalogInterface() const {
        return A_INTERFACE;
    }

private:
    std::string WATERBOT_HOST;
    std::string WATERBOT_API_KEY;
    std::string WATERBOT_UNIQUE_NAME;
    std::vector<Plant> WATERBOT_PLANTS;
    int DAEMON_LOG_VERBOSITY;
    std::string A_INTERFACE;
};

class Config {
public:
    static WaterBotConfig ReadConfig(std::string Path);
    static void GenerateConfigFile(std::string FilePath);
    template<typename T>
    static int ReadCustomIntegerField(std::string Category, std::string Name, T Default)
    {
        INIReader Reader(ConfigPath);
        return (int) Reader.GetInteger(Category, Name, Default);
    }
};

#define WATERBOT_CONFIG_FILE \
"[Daemon]\n"\
"LogVerbosity=3 ;0 to 9\n"\
"[Interface]\n"\
";mcp3008/3004, and more to come maybe...\n"\
"AnalogInterface=mcp3008\n"\
"[Mcp3008]\n"\
"SpiChannel=0\n"\
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
