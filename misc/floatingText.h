#pragma once

#include <string>
#include <vector>
#include "../raylib/raylib.h"

class FloatingText
{
public:
    FloatingText() = default;
    
    void Show(const std::string& text, Vector2 origin, float lifetime, Color color = WHITE);

    void Update(float dt);
    void Draw();

    void SetFollowOffset(Vector2 offset);

private:
    struct Instance
    {
        std::string text;
        Vector2 pos;
        Vector2 velocity;
        float lifetime = 0.0f;
        float time = 0.0f;
        Color color = WHITE;
    };

    std::vector<Instance> _texts;

    Vector2 _followOffset = {0, 0};
};