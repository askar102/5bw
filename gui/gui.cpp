#include "gui.h"

void Gui::SetResource(TextureResource* resource)
{
    _sprite.SetResource(resource);
}

void Gui::SetPosition(Vector2 position)
{
    _sprite.SetPosition(position);
}

void Gui::SetVisible(bool visible)
{
    _visible = visible;
}

void Gui::Draw()
{
    if (_visible)
    {
        _sprite.Draw();
    }
}

SpriteV2& Gui::GetSprite()
{
    return _sprite;
}