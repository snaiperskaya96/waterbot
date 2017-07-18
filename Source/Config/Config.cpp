//
// Created by Jury Verrigni on 12/07/2017.
//

#include <Utils/Ini/INIReader.h>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include "Config.h"

WaterBotConfig Config::ReadConfig(std::string Path)
{
    const std::string ConfigPath = Path;
    INIReader Reader(ConfigPath);
    if (Reader.ParseError() < 0) {
        printf("Couldn't find %s. Make sure to run WaterBot --generate-config.\n", ConfigPath.c_str());
        exit(1);
    }

    std::string BotName = Reader.Get("General", "BotName", "Unknown");
    std::string Host = Reader.Get("General", "Host", "Unknown");
    std::string ApiKey = Reader.Get("General", "ApiKey", "");

    std::vector<Plant> Plants;
    int NumberOfPlants = (uint8_t) (Reader.GetInteger("General", "NumberOfPlants", 0) + 1);

    for (int Index = 1; Index < NumberOfPlants; Index++) {
        std::string PlantName = "Plant_" + std::to_string(Index);
        std::string Name = Reader.Get(PlantName, "Name", "Unknown");
        int Pin = (int) Reader.GetInteger(PlantName, "HumidityPin", 0);
        const Plant MyPlant(Name, Pin);
        Plants.push_back(MyPlant);
    }

    int LogVerbosity = (int) Reader.GetInteger("Daemon", "LogVerbosity", 3);

    std::string AnalogInterface = Reader.Get("Interface", "AnalogInterface", "");

    return WaterBotConfig(Host, ApiKey, BotName, Plants, LogVerbosity, AnalogInterface);
}

void Config::GenerateConfigFile(std::string FilePath)
{
    struct stat Info;
    if (stat(FilePath.c_str(), &Info) != 0
        || !(Info.st_mode & S_IFDIR)
    ) {
        printf("%s is not a valid directory.\n", FilePath.c_str());
        exit(1);
    }

    if (FilePath.back() != '/')
        FilePath += "/";

    std::ofstream ConfigFile(FilePath + "WaterBot.ini");
    ConfigFile << WATERBOT_CONFIG_FILE;
    ConfigFile.close();
}

template<typename T>
T Config::ReadCustomField(std::string Category, std::string Name, T Default)
{
    INIReader Reader(ConfigPath);
    if (Reader.ParseError() < 0) {
        printf("Couldn't find %s. Make sure to run WaterBot --generate-config.\n", ConfigPath.c_str());
        exit(1);
    }

    if (typeid(T) == typeid(std::string)) {
        return Reader.Get(Category, Name, Default);
    }
    if (typeid(T) == typeid(int)) {
        return (int) Reader.GetInteger(Category, Name, Default);
    }
    if (typeid(T) == typeid(std::string)) {
        return Reader.GetReal(Category, Name, Default);
    }
    if (typeid(T) == typeid(int)) {
        return Reader.GetBoolean(Category, Name, Default);
    }

    return nullptr;
}
