#include "window.h"

Window::Window(Button* hook, Vector2 pos, Vector2 size, std::function<void()> onEnter) 
    : _hookButton(hook), _pos(pos), _size(size), _onEnter(onEnter)
{
    _bgRes = {LoadTexture("resources/windowBackground.png"), {}};
    _sprite.SetResource(&_bgRes);

    _exitRes = {LoadTexture("resources/windowCloseButton.png"), {}};
    _exitButton.GetSprite().SetResource(&_exitRes);

    Vector2 exitPos = {_pos.x + _size.x / 2.0f, _pos.y - _size.y / 2.0f}; 
    _exitButton.SetPosition(exitPos);
    _exitButton.GetSprite().SetSize({50, 50});

    _sprite.SetPosition(_pos);
    _sprite.SetSize(_size);

    SetVisible(false);

    // exit logic
    _exitButton.SetOnClick([this] () {
        Show(false);
    });
}

void Window::Draw() 
{
    if (_visible) 
    {
        _sprite.Draw();
        _exitButton.Draw();

        for (const auto& btn : _additionalButtons) {
            btn->Draw();
        }

        for (const auto& el : _elements) {
            el->Draw();
        }
    }
}

void Window::Update() 
{
    // hook button
    if (_hookButton) 
    {
        _hookButton->SetOnClick([this] () {
            Show(!_visible);
        });
    }

    //exit button
    _exitButton.Update();

    // additionals buttons
    if (!_additionalButtons.empty()) {
        for (const auto& btn : _additionalButtons) {
            btn->Update();
        }
    }

    if (_visible) {
        for (const auto& el : _elements) {
            el->Update();
        }
    }
}


void Window::Show(bool value) 
{
    _visible = value;
}

void Window::AddButton(std::unique_ptr<Button> newButton) 
{
    _additionalButtons.push_back(std::move(newButton));
}

void Window::AddButtons(std::vector<std::unique_ptr<Button>>&& newButtonsVec)
{
    _additionalButtons.insert(
        _additionalButtons.end(),
        std::make_move_iterator(newButtonsVec.begin()),
        std::make_move_iterator(newButtonsVec.end())
    );
}

Gui* Window::AddElement(std::unique_ptr<Gui> element)
{
    if (!element) return nullptr;

    Gui* raw = element.get();
    _elements.push_back(std::move(element));
    return raw;
}