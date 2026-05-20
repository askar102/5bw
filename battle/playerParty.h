#pragma once

#include <array>
#include <memory>

#include "party.h"

#include "../misc/configReader.h"

class PlayerParty : public Party {
public:
    PlayerParty();

    void Init() override;

};