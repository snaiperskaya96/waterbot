//
// Created by Jury Verrigni on 12/07/2017.
//

#ifndef WATERBOT_RASPI_HTTP_H
#define WATERBOT_RASPI_HTTP_H


#include <Config/Config.h>
#include <Utils/restclient-cpp/restclient.h>
#include <Utils/restclient-cpp/connection.h>

class Http {
public:
    static Http& GetInstance()
    {
        static Http Instance;
        return Instance;
    }
    Http(Http const&) = delete;
    void operator=(Http const&) = delete;

    void Init()
    {
        RestClient::init();
        Connection = new RestClient::Connection(Config->GetHost());
        RestClient::HeaderFields Headers;
        Headers["wb_token"] = Config->GetApiKey();
        Headers["wb_id"] = Config->GetUniqueName();
        Connection->SetHeaders(Headers);
    };

    void SetConfig(WaterBotConfig* Config)
    {
        this->Config = Config;
    }

    void RegisterPlant(Plant MyPlant);
    void UpdatePlant(Plant* MyPlant);

private:
    WaterBotConfig* Config;
    RestClient::Connection* Connection;
private:
    Http() {};
};


#endif //WATERBOT_RASPI_HTTP_H
