#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <functional>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"

#include "../misc/text.h"

class Typewritter {
public:
    void SpawnAt(std::string text, Vector2 position, float speed = 10.0f, bool resetInEnd = false);
    void SpawnAt(std::vector<std::string> lines, Vector2 position, float speed = 10.0f, bool resetInEnd = false);

    void Reset();
    void SkipAnimation();

    void Draw();
    void Update(float dt);

    void SetSpeed(float charsPerSecond);

private:
    void StartLine(const std::string& text);
    void AdvanceQueue();

    Vector2 _pos;

    std::vector<std::string> _queue;
    size_t _queueIndex = 0;

    std::string _text;

    bool _resetInEnd = false;
    bool _visible = false;
    int32_t _framesCounter = 0;

    float _speed = 10.0f;
    float _charsOpened = 0;
};