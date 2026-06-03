#include "dialogPopup.h"
#include <cstdio>

std::vector<std::string> DialogPopUp::_text;

DialogPopUp::DialogPopUp(const SpriteV2* entity) 
{
    _anchor = entity;
    _rect = {0, 0, 220, 80};
}

void DialogPopUp::Show(uint32_t dialogID)
{
    _text = ConfigReader::GetDialogFromConfig(dialogID);

    if (!_text.empty())
    {
        // for (std::string str : text) {
        //     printf((str + '\n').c_str());
        // }
        _visible = true;
    }   
}

void DialogPopUp::Draw()
{
    _rect = {0, 0, 220, 80};
    if (_visible) 
    {   
        DrawRectanglePro(_rect, {0, 0}, 90.0f, WHITE);
    }
    
}

void DialogPopUp::Draw(const SpriteV2* entity)
{
    _anchor = entity;

    if (_visible)
    {
        _rect.x = entity->GetPosition().x;
        _rect.y = entity->GetPosition().y - 100;
        DrawRectanglePro(_rect, {0, 0}, 0.0f, WHITE);
    }
}

void DialogPopUp::Update(float dt)
{
    if (_anchor) 
    {
        _rect.x = _anchor->GetPosition().x;
        _rect.y = _anchor->GetPosition().y;
    }
}