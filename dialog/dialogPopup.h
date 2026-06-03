#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

class DialogPopUp {
public:
    void Show(const SpriteV2& entity, uint32_t dialogID);
    void Next();

private:
    std::vector<std::string> text;
};