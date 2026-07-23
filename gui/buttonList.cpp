#include "buttonList.h"
#include "../misc/inputBridge.h"

void ButtonList::Draw()
{
    if (!_visible) return;

    for (int i = 0; i < static_cast<int>(_buttons.size()); ++i)
    {
        _buttons[i]->Draw();

        if (i == _selectedIndex)
        {
            Vector2 btnPos  = _buttons[i]->GetSprite().GetPosition();
            Vector2 btnSize = _buttons[i]->GetSprite().GetSize();

            float cx = btnPos.x - btnSize.x * 0.5f - CURSOR_SIZE * 2.0f;
            float cy = btnPos.y;

            DrawTriangle(
                { cx,                    cy - CURSOR_SIZE },
                { cx,                    cy + CURSOR_SIZE },
                { cx + CURSOR_SIZE * 2,  cy               },
                WHITE
            );
        }
    }
}

void ButtonList::Update() 
{
    if (_buttons.empty()) return;

    if (InputBridge::KeyPressed(KEY_DOWN))
    {
        _selectedIndex = (_selectedIndex + 1) % static_cast<int>(_buttons.size());
    }
        

    if (InputBridge::KeyPressed(KEY_UP))
    {
        _selectedIndex = (_selectedIndex - 1 + static_cast<int>(_buttons.size()))
                         % static_cast<int>(_buttons.size());
    }

    if (InputBridge::KeyPressed(KEY_ENTER))
        _buttons[_selectedIndex]->UseOnClick();

    for (int i = 0; i < static_cast<int>(_buttons.size()); ++i)
    {
        if (i == _selectedIndex)
            _buttons[i]->UseOnTouch();
        else _buttons[i]->SetTextColor(WHITE);

        _buttons[i]->Update();
        
    }
}

void ButtonList::Add(std::unique_ptr<Button> newButton) 
{
    if (!newButton) return;

    Vector2 base = _sprite.GetPosition();
    Vector2 pos  = { base.x, base.y + static_cast<float>(_buttons.size()) * SPACING };

    newButton->GetSprite().SetPosition(pos);

    _buttons.push_back(std::move(newButton));

}

void ButtonList::SetIndex(int index)
{
    _selectedIndex = index;
}

void ButtonList::Clear() 
{
    _buttons.clear();
    _selectedIndex = 0;
}


