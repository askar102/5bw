/**
 * @file menuState.cpp
 * @author askar102
 * @brief Menu scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "menuState.h"
#include <memory>

void MenuState::HandleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        startPressed = true;
    }
}

void MenuState::Draw() {
    ClearBackground(BLACK);
    DrawText("currentState: menu", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: press Enter", 0, 30, 20, WHITE);

    _gui.Draw(); 
}

void MenuState::Update(float dt) {
    if (startPressed) {
        startPressed = false;
        stateMachine->ChangeState(std::make_unique<MapState>());
        return;
    }

    _gui.Update();

    if (IsKeyPressed(KEY_H))
    {
        SpriteV2::SetDrawHitboxes(!SpriteV2::GetDrawHitboxes());
    }
}
void MenuState::OnEnter() {
    InitNewGui();
}
    

void MenuState::OnExit() {
    _gui.Clear();
}


void MenuState::InitNewGui()
{
    auto buttons = std::make_unique<ButtonList>();
    buttons->SetPosition({200, 300});

    auto newGameButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Start",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            startPressed = true;
        },
        PositionType::Left
    );

    Button* btnPtr = newGameButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(GREEN);
    });

    buttons->Add(std::move(newGameButton));

    auto continueButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Continue",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            startPressed = true;
        },
        PositionType::Left
    );

    btnPtr = continueButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(GREEN);
    });

    buttons->Add(std::move(continueButton));

    _gui.Add(std::move(buttons));
}



void MenuState::InitGui() {
    std::vector<TextureID> names = { TextureID::GuiNewGameButton, TextureID::GuiContinueButton, TextureID::GuiTradesButton };

    // 150 - screen start pos
    
    auto menuBackground = std::make_unique<Gui>();

    Gui* bg = menuBackground.get();
    bg->SetResource(&Game::GetResources().Get(TextureID::MenuBackground));
    bg->SetPosition({400, 300});

    _gui.Add(std::move(menuBackground));

    auto newGameButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "New game",
        &Game::GetResources().Get(names[0]),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            startPressed = true;
        }
    );

    // EXAMPLE OF BUTTON MANIPULATION:
    // Button* btnPtr = newGameButton.get();

    // btnPtr->SetOnTouch([btnPtr]() {
    //     btnPtr->GetSprite().SetBrightness(1.5f);
    // });

    _gui.Add(std::move(newGameButton));


    _gui.Add(std::make_unique<Button>(
        Vector2{150, 360}, // y+60
        Vector2{300, 50},
        "Continue",
        &Game::GetResources().Get(names[1]),
        [this]() {
             // stub
        }
    ));

    _gui.Add(std::make_unique<Button>(
        Vector2{150, 420}, // y+60
        Vector2{300, 50},
        "Trades",
        &Game::GetResources().Get(names[2]),
        [this]() {
             // stub
        }
    ));

     
}
