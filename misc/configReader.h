#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <fstream>
#include <memory>

#include "../raylib/raylib.h"

#include "../battle/battleEntity.h"
#include "../external/json.h"


class ConfigReader {
public:
    static std::array<std::string, 4> GetPlayerPartyFromConfig();

    static BattleEntity GetCharacterFromConfig(std::string name);

    static std::vector<std::string> GetDialogFromConfig(int32_t dialogID);

private:
    static AbilityType ParseAbilityType(const std::string& type);
};