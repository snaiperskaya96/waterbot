//
// Created by Jury Verrigni on 18/07/2017.
//

#include <ThermometerInterface/Adapters/Dht22.h>
#include "ThermometerInterface.h"

void ThermometerInterface::Init()
{
    if (!Config->Thermometer) return;
    std::string I = Config->ThermometerInterface;
    if (I.empty()) return;
    if (I == "dht22") {
        Interface = new Dht22();
        Interface->Init();
    }
}

void ThermometerInterface::Update() {
    if (Interface != nullptr) {
        Interface->Update();
    }
}


