#pragma once

#include <deque>
#include "../entities/spriteV2.h"

struct GhostFrame {
    Vector2 position;
    float rotation;
    float alpha;
};

class GhostTrail {
public:
    // maxGhosts - сколько копий максимум
    // fadeSpeed - как быстро исчезают
    // interval - как часто создаём новый ghost (в секундах)
    void Init(int maxGhosts = 6, float fadeSpeed = 8.0f, float interval = 0.03f);

    void Update(float dt, const SpriteV2& sprite);
    void Draw(const SpriteV2& sprite) const;

    void SetEnabled(bool enabled) { _enabled = enabled; }

private:
    std::deque<GhostFrame> _frames;

    int _maxGhosts = 6;
    float _fadeSpeed = 8.0f;
    float _interval = 0.03f;
    float _timer = 0.0f;
    bool _enabled = false;
};