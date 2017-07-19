/** 
*  WaterBot
*
*  Created by Jury Verrigni at SkayaHack.com
*/

#include "WaterBot.h"
#include <unistd.h>
#include <Http/Http.h>
#include <Input/InputParser.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <sys/signal.h>
#include <Log/loguru.h>
#include <AnalogInterface/AnalogInterface.h>
#include <ThermometerInterface/ThermometerInterface.h>

#ifdef WATERBOT_RASPI
#include <wiringPi.h>
#endif

#define PID_FILE_NAME "/tmp/waterbot.pid"

void RegisterPlants(WaterBotConfig Conf)
{
    for (Plant MyPlant : Conf.GetPlants()) {
        Http::GetInstance().RegisterPlant(MyPlant);
    }
}

void Delay(int Milis)
{
    usleep ((useconds_t) (Milis * 1000));
}

void Loop(WaterBotConfig Conf)
{
    while(true) {
        for (Plant MyPlant : Conf.GetPlants()) {
            MyPlant.Update();
        }
        Delay(10000);
    }
}

int main(int ArgC, char** ArgV)
{
    InputParser Parser(ArgC, ArgV);
    std::string ConfigPath = "./WaterBot.ini";

    if (Parser.ArgumentExists("--generate-config")) {
        std::string Path = Parser.GetArgumentAsString("--generate-config");
        if (Path.empty()) {
            WDEBUG("Generating config file within the executable path.\n");
            Config::GenerateConfigFile("./");
        } else {
            WDEBUG("Generating config file at %s\n", Path.c_str());
            Config::GenerateConfigFile(Path);
        }
        exit(0);
    }

    if (Parser.ArgumentExists("-daemon")) {
        ConfigPath = "/etc/WaterBot/WaterBot.ini";
    }

    if (Parser.ArgumentExists("--config")) {
        ConfigPath = Parser.GetArgumentAsString("--config");
    }

    WaterBotConfig Conf = Config::ReadConfig(ConfigPath);

    AnalogInterface::GetInstance().SetConfig(&Conf);

    if (Parser.ArgumentExists("-daemon")) {
        loguru::init(ArgC, ArgV);
        loguru::add_file("/var/log/waterbot.log", loguru::Append, Conf.GetDaemonLogVerbosity());
        WDEBUG("Daemonising process\n");
        Daemonise();
    }

#ifdef WATERBOT_RASPI
    wiringPiSetup();
#endif

    printf("\nWaterBot v.%s started.\n", WATERBOT_VERSION);

    WDEBUG("WaterBot Debugging enabled.\n");

    Http::GetInstance().SetConfig(&Conf);
    Http::GetInstance().Init();
    ThermometerInterface::GetInstance().SetConfig(&Conf);
    RegisterPlants(Conf);
    Loop(Conf);
    return 0;
}

void Daemonise()
{
    LOG_SCOPE_FUNCTION(INFO);
    pid_t Pid = 0;
    int FileDescriptor;

    Pid = fork();

    if (Pid < 0) {
        LOG_F(ERROR, "First fork failed. Pid < 0");
        exit(EXIT_FAILURE);
    }

    if (Pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        LOG_F(ERROR, "First fork failed. setsid < 0");
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, SIG_IGN);

    Pid = fork();

    if (Pid < 0) {
        LOG_F(ERROR, "Second fork failed. Pid < 0");
        exit(EXIT_FAILURE);
    }

    if (Pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    chdir("/etc/waterbot/");

    for (FileDescriptor = (int) sysconf(_SC_OPEN_MAX); FileDescriptor > 0; FileDescriptor--) {
        close(FileDescriptor);
    }

    /* Reopen stdin (fd = 0), stdout (fd = 1), stderr (fd = 2) */
    stdin = fopen("/dev/null", "r");
    stdout = fopen("/dev/null", "w+");
    stderr = fopen("/dev/null", "w+");

    /* Try to write PID of daemon to lockfile */
    if (PID_FILE_NAME != NULL)
    {
        int PidFileDescriptor = -1;
        char PidString[256];
        PidFileDescriptor = open(PID_FILE_NAME, O_RDWR|O_CREAT, 0640);
        if (PidFileDescriptor < 0) {
            LOG_F(ERROR, "Cannot open PID file");
            exit(EXIT_FAILURE);
        }
        if (lockf(PidFileDescriptor, F_TLOCK, 0) < 0) {
            LOG_F(ERROR, "Cannot lock PID file");
            exit(EXIT_FAILURE);
        }
        /* Get current PID */
        sprintf(PidString, "%d\n", getpid());
        /* Write PID to lockfile */
        write(PidFileDescriptor, PidString, strlen(PidString));
    }
}