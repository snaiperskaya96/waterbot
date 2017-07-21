//
// Created by Jury Verrigni on 12/07/2017.
//

#include <cstdlib>
#include <Utils/restclient-cpp/restclient.h>
#include <WaterBot.h>
#include "Http.h"

void Http::RegisterPlant(Plant MyPlant)
{
    std::string Payload = "name=" + MyPlant.GetName();
    WDEBUG("Http::RegisterPlant: Posting %s to /api/plant\n", Payload.c_str());
    RestClient::Response Resp = Connection->post("/api/plant", Payload);

    WDEBUG("Http::RegisterPlant: Result: %s\n", Resp.body.c_str());
}

void Http::UpdatePlant(Plant* MyPlant)
{
    std::string Payload = "name=" + MyPlant->GetName() + "&humidity=" + std::to_string(MyPlant->GetHumidityPercentage());
    WDEBUG("Http::UpdatePlant: Posting %s to /api/plant/update\n", Payload.c_str());
    RestClient::Response Resp = Connection->post("/api/plant/update", Payload);

    WDEBUG("Http::UpdatePlant: Result: %s\n", Resp.body.c_str());
}

void Http::PostCustomData(std::map<std::string, std::string> Data)
{
    std::string Payload;
    for (auto const& Iterator : Data) {
        Payload += Iterator.first + "=" + Iterator.second + "&";
    }
    WDEBUG("Http::PostCustomData: Posting %s to /api/custom-data\n", Payload.c_str());
    RestClient::Response Resp = Connection->post("/api/custom-data", Payload);

    WDEBUG("Http::PostCustomData: Result: %s\n", Resp.body.c_str());
}