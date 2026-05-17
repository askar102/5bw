#pragma once

#include <array>
#include <string>
#include <fstream>

#include "../raylib/raylib.h"

#include "../external/json.h"

class ConfigReader {
public:
    static std::array<std::string, 4> GetPartyFromConfig();
};