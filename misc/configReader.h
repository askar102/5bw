#pragma once

#include <array>
#include <string>
#include <fstream>
#include <memory>

#include "../raylib/raylib.h"

#include "../battle/battleEntity.h"
#include "../external/json.h"

class ConfigReader {
public:
    static std::array<std::string, 4> GetPartyFromConfig();

    static BattleEntity GetCharacterFromConfig(std::string name);
};