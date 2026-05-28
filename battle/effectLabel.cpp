#include "effectLabel.h"
#include "../core/game.h"

void EffectLabel::Show(const std::string& textureName, float duration)
{
    _textureName = textureName;
    _duration    = duration;
    _timer       = duration;
}

void EffectLabel::Update(float dt)
{
    if (_timer > 0.0f)
        _timer -= dt;
}

void EffectLabel::Draw(Vector2 anchorPos, Vector2 anchorSize) const
{
    if (_timer <= 0.0f) return;

    TextureResource& tex = Game::GetResources().Get(_textureName);

    float labelW = static_cast<float>(tex.texture.width);

    // fade-out в последние 0.5 секунды
    float alpha = (_timer < 0.5f) ? (_timer / 0.5f) : 1.0f;

    DrawTexture(
        tex.texture,
        static_cast<int>(anchorPos.x - labelW * 0.5f),
        static_cast<int>(anchorPos.y + anchorSize.y * 0.5f + 4.0f),
        Fade(WHITE, alpha)
    );
}