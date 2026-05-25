#include "button.h"

#include "../core/game.h"

Button::Button() {
    SetResource(&Game::GetResources().Get(TextureID::GuiButton));
}

Button::Button(Vector2 pos, Vector2 size, std::string label, std::function<void()> onClick) 
    : _label(label), _onClick(onClick)
{
    GetSprite().SetSize(size);
    GetSprite().SetPosition(pos);
}

void Button::SetLabel(const std::string& text) {
    _label = text;
}

void Button::SetOnClick(std::function<void()> callback) {
    _onClick = callback;
}

void Button::Update() {
    if (!_visible) return;

    Vector2 mouse = GetMousePosition();
    Rectangle rect = _sprite.GetRect();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
        && CheckCollisionPointRec(mouse, rect)
        && _onClick)  // проверяем что callback задан
    {
        _onClick();
    }
}

void Button::Draw() {
    if (!_visible) return;
    
    _sprite.Draw();

    // текст по центру кнопки
    Vector2 pos = _sprite.GetPosition();
    Vector2 size = _sprite.GetSize();
    int fontSize = 16;
    int textWidth = MeasureText(_label.c_str(), fontSize);
    
    DrawText(
        _label.c_str(),
        static_cast<int>(pos.x - textWidth / 2),
        static_cast<int>(pos.y - fontSize / 2),
        fontSize,
        WHITE
    );
}