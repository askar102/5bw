#pragma once

#include "../raylib/raylib.h"
#include "../core/resourceManager.h"

class EffectLabel {
public:
    // textureName - имя текстуры из ResourceManager::Get(string)
    void Show(const std::string& textureName, float duration);
    void Update(float dt);
    void Draw(Vector2 anchorPos, Vector2 anchorSize) const;

    bool IsVisible() const { return _timer > 0.0f; }

private:
    std::string _textureName;
    float _timer    = 0.0f;
    float _duration = 0.0f;
};