#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

#include "../misc/configReader.h"

class DialogPopUp {
public:
    static void Show(const SpriteV2* entity, uint32_t dialogID);
    void Next();

private:
    static std::vector<std::string> text;
};