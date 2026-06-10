#include "window.h"

Window::Window(Button* hook, Vector2 pos, Vector2 size, std::function<void()> onEnter) 
    : _hookButton(hook), _pos(pos), _size(size), _onEnter(onEnter)
{
    _bgRes = {LoadTexture("resources/windowBackground.png"), {}};
    _sprite.SetResource(&_bgRes);

    _exitRes = {LoadTexture("resources/windowCloseButton.png"), {}};
    _exitButton.SetResource(&_exitRes);
    _exitButton.SetPosition({300, 400});

    _sprite.SetPosition(_pos);
    _sprite.SetSize(_size);
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