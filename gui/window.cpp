#include "window.h"

Window::Window(Button* hook, Vector2 pos, Vector2 size, std::function<void()> onEnter) 
    : _hookButton(hook), _pos(pos), _size(size), _onEnter(onEnter)
{
    _bgRes = {LoadTexture("resources/windowBackground.png"), {}};
    _sprite.SetResource(&_bgRes);

    _exitRes = {LoadTexture("resources/windowCloseButton.png"), {}};
    _exitButton.SetResource(&_exitRes);

    Vector2 exitPos = {_pos.x + _size.x / 2.0f, _pos.y - _size.y / 2.0f}; 
    _exitButton.SetPosition(exitPos);
    _exitButton.SetSize({50, 50});

    _sprite.SetPosition(_pos);
    _sprite.SetSize(_size);

    SetVisible(false);
}

void Window::Draw() 
{
    if (_visible) 
    {
        _sprite.Draw();
        _exitButton.Draw();    
    }
}

void Window::Update() {
    // hook button
    if (_hookButton) {
        _hookButton->SetOnClick([this] () {
            Show(!_visible);
        });
    }
}


void Window::Show(bool value) {
    _visible = value;
}