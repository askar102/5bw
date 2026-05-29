#include "minigame.h"
#include "../core/game.h"
#include "battleEntity.h"

void Minigame::Play()
{
}

void Minigame::Update(float dt)
{
    _background.Update(dt);
}

void Minigame::Draw(SpriteV2& unit)
{
    _background.SetResource(&Game::GetResources().Get("minigameBackground"));
    _hole.SetResource(&Game::GetResources().Get("minigameHole"));
    _cursor.SetResource(&Game::GetResources().Get("minigameCursor"));

    _background.SetSize({100, 40});    
    _background.SetAlpha(0.7f);

    _background.Draw();
    _hole.Draw();
    _cursor.Draw();
}