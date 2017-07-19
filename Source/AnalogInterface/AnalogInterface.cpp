//
// Created by Jury Verrigni on 18/07/2017.
//

#include <AnalogInterface/Adapters/Mcp3008.h>
#include <stdexcept>
#include "AnalogInterface.h"

void AnalogInterface::Init()
{
    if (Config == nullptr) {
        throw std::runtime_error("AnalogInterface::Init: Config not set");
    }

    std::string AnalogInterface = Config->GetAnalogInterface();
    if (AnalogInterface == "mcp3008" || AnalogInterface == "mcp3004") {
        Interface = new Mcp3008();
        Interface->Init(Config);
    } else {
        throw std::runtime_error("AnalogInterface::Init: AnalogInterface not set");
    }
}

int AnalogInterface::AnalogRead(int Pin)
{
     return Interface != nullptr ? Interface->AnalogRead(Pin) : 0;
}
