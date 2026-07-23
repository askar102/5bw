#include "button.h"
#include "../misc/inputBridge.h"

#include "../core/game.h"

Button::Button() {
    SetResource(&Game::GetResources().Get(TextureID::GuiButton));
}

Button::Button(Vector2 pos, Vector2 size, std::string label, std::function<void()> onClick, PositionType textPositionType) 
    : _label(label), _onClick(onClick), _textPositionType(textPositionType)
{
    GetSprite().SetSize(size);
    GetSprite().SetPosition(pos);
    SetResource(&Game::GetResources().Get(TextureID::GuiButton));
}

Button::Button(Vector2 pos, Vector2 size, std::string label, TextureResource* resource, std::function<void()> onClick, PositionType textPositionType)
    : _label(label), _onClick(onClick), _textPositionType(textPositionType)
{
    SetResource(resource);
    GetSprite().SetSize(size);
    GetSprite().SetPosition(pos);
}

Button::Button(Vector2 pos, Vector2 size, std::string label, TextureResource* resource, std::function<void()> onClick, std::function<void()> onTouch, PositionType textPositionType)
    : _label(label), _onClick(onClick), _onTouch(onTouch), _textPositionType(textPositionType)
{
    SetResource(resource);
    GetSprite().SetSize(size);
    GetSprite().SetPosition(pos);
}

void Button::SetLabel(const std::string& text) {
    _label = text;
}

void Button::SetOnClick(std::function<void()> callback) {
    _onClick = callback;
}

void Button::SetOnTouch(std::function<void()> callback) {
    _onTouch = callback;
}

void Button::UseOnClick()
{
    if (_onClick)
    {
        _onClick();
    } 
}

void Button::UseOnTouch()
{
    if (_onTouch)
    {
        _onTouch();
    } 
}

void Button::SetTextColor(Color newColor)
{
    _textColor = newColor;
}

void Button::SetTextPositionType(PositionType newType)
{
    _textPositionType = newType;
}

void Button::Update() {
    if (!_visible) return;

    // default value
    GetSprite().SetBrightness(1.0f);

    Vector2 mouse = Game::GetWorldMouse();
    Rectangle rect = _sprite.GetRect();

    if (InputBridge::MouseButtonPressed(MOUSE_LEFT_BUTTON)
        && CheckCollisionPointRec(mouse, rect)
        && _onClick) 
    {
        _onClick();
    }

    if (CheckCollisionPointRec(mouse, rect) && _onTouch)
    {
        _onTouch();
    }
    
    // default, without onTouch init
    if (CheckCollisionPointRec(mouse, rect) && !_onTouch)
    {
        GetSprite().SetBrightness(1.5f);
    }
}

void Button::Draw() {
    if (!_visible) return;
    
    _sprite.Draw();

    Vector2 pos = _sprite.GetPosition();
    Vector2 size = _sprite.GetSize();
    int textWidth = MeasureText(_label.c_str(), _textFontSize);
    constexpr float textPadding = 10.0f;
    float textX = pos.x - (float)textWidth / 2.0f;

    switch (_textPositionType)
    {
        case PositionType::Left:
            textX = pos.x - size.x / 2.0f + textPadding;
            break;
        case PositionType::Right:
            textX = pos.x + size.x / 2.0f - (float)textWidth - textPadding;
            break;
        case PositionType::Center:
        default:
            break;
    }
    
    DrawTextEx(
        Game::GetResources().GetFont(),
        _label.c_str(),
        (Vector2){ textX, pos.y - (float)_textFontSize / 2},
        _textFontSize,
        2,
        _textColor
    );
}
