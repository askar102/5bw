#include "window.h"

Window::Window(Button* hook, Vector2 pos, Vector2 size, std::function<void()> onEnter) 
    : _hookButton(hook), _pos(pos), _size(size), _onEnter(onEnter)
{
    TextureResource bgRes = {LoadTexture("resources/windowBackground.png"), {}};
    SetResource(&bgRes);

    TextureResource exitRes = {LoadTexture("resources/closeButton.png"), {}};
    _exitButton.SetResource(&exitRes);
    _exitButton.SetPosition({300, 400});
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