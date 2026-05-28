#include "effectIcon.h"
#include "../core/game.h"
#include "battleEntity.h"

void EffectIcon::Show(const std::string& textureName, float duration)
{
    _textureName = textureName;
    _duration    = duration;
    _timer       = duration;
}

void EffectIcon::Update(float dt)
{
    if (_timer > 0.0f)
        _timer -= dt;
}

void EffectIcon::Draw(SpriteV2& unit)
{
    if (_timer <= 0.0f) return;

    TextureResource& tex = Game::GetResources().Get(_textureName);
    _sprite.SetResource(&tex);
    _sprite.SetSize({50, 50});
    _sprite.SetAlpha(1.0f);

    // fade-out в последние 0.5 секунды
    float alpha; // = (_timer < 0.5f) ? (_timer / 0.5f) : 0.7f;
    if (_timer < 0.5f) 
    {
        alpha = _timer / 0.5f;
        _sprite.SetFlashing(true);
    } 
    else 
    {
        alpha = 0.7f;
    } 

    float posY = unit.GetPosition().y;

    Rectangle rect = unit.GetWorldRect();
    Vector2 topLeft = { rect.x, rect.y };

    _sprite.SetAlpha(alpha);
    _sprite.SetPosition(topLeft);

    _sprite.SetPosition({topLeft});
    _sprite.Draw();
}