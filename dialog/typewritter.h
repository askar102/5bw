#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"

class Typewritter {
public:
    void SpawnAt(std::string text, Vector2 position, bool resetInEnd = false);

    void Reset();
    void SkipAnimation();

    void Draw();
    void Update(float dt);
private:
    Vector2 _pos;
    std::string _text;

    bool _resetInEnd = false;

    bool _visible = false;
    int32_t _framesCounter = 0;
};
