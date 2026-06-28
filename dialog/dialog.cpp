#include "dialog.h"

TextureResource Dialog::_storyTexture;
TextureResource Dialog::_defaultTexture;

SpriteV2 Dialog::_storyBackgroud;
SpriteV2 Dialog::_defaultBackground;

void Dialog::Init()
{
    _storyTexture = {LoadTexture("resources/dialog_story.png"), {}};
    _defaultTexture = {LoadTexture("resources/dialog_default.png"), {}};

    _storyBackgroud.SetResource(&_storyTexture);
    _defaultBackground.SetResource(&_defaultTexture);
}

void Dialog::Show(int id, DialogMode mode, std::function<void()> onClose)
{
    _mode = mode;
    _visible = true;
}

void Dialog::Update(float dt)
{
    if (_mode == DialogMode::StoryCenter || _mode == DialogMode::StoryDown) _storyBackgroud.Update(dt);
    if (_mode == DialogMode::Mind || _mode == DialogMode::Npc) _defaultBackground.Update(dt);
}

void Dialog::Draw()
{
    if (_visible) 
    {   
        if (_mode == DialogMode::StoryCenter || _mode == DialogMode::StoryDown) _storyBackgroud.Draw();
        if (_mode == DialogMode::Mind || _mode == DialogMode::Npc) _defaultBackground.Draw();
    }
    
}



// private

void Dialog::LoadLine()
{

}

void Dialog::NextLine()
{

}

void Dialog::SelectAnswer(int32_t index)
{

}