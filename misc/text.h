#pragma once

#include <string>
#include <cstdint>

#include "../raylib/raylib.h"

class Text {
public:
    static void DrawText(const std::string& text, Vector2 pos, int size = 20, Color color = WHITE, float spacing = 1.0f);

    static void DrawText(const std::string& text, int32_t posX, int32_t posY, int size = 20, Color color = WHITE, float spacing = 1.0f);

    static void Init();

private:
    static Font _font;
    static bool _inited;
};