#include "dialog.h"
#include "typewritter.h"

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

    _storyBackgroud.SetPosition({640/2.0f, 480/2.0f});
    _storyBackgroud.SetAlpha(0.6f);
}

void Dialog::Show(std::string text, DialogMode mode, std::function<void()> onClose)
{
    _mode = mode;
    _visible = true;

    _typewritter.SpawnAt(text, {640/2.0f-200.0f, 480/2.0f-30.0f}, 10.0f, true);
    _typewritter.InOver([this] () {
        _visible = false;
    });
}

void Dialog::Update(float dt)
{
    if (_mode == DialogMode::StoryCenter || _mode == DialogMode::StoryDown) _storyBackgroud.Update(dt);
    if (_mode == DialogMode::Mind || _mode == DialogMode::Npc) _defaultBackground.Update(dt);
    _typewritter.Update(dt);
}

void Dialog::Draw()
{
    if (_visible) 
    {   
        if (_mode == DialogMode::StoryCenter || _mode == DialogMode::StoryDown) _storyBackgroud.Draw();
        if (_mode == DialogMode::Mind || _mode == DialogMode::Npc) _defaultBackground.Draw();
    }

    _typewritter.Draw();
    
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