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
    RestClient::Response Resp = Connection->post("/api/plant", Payload);

    WDEBUG("Http::RegisterPlant: Result: %s\n", Resp.body.c_str());
}

void Http::UpdatePlant(Plant* MyPlant)
{
    std::string Payload = "name=" + MyPlant->GetName() + "&humidity=" + std::to_string(MyPlant->GetHumidityPercentage());
    RestClient::Response Resp = Connection->post("/api/plant/update", Payload);

    WDEBUG("Http::UpdatePlant: Result: %s\n", Resp.body.c_str());
}
