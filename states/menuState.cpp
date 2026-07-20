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
#include "raylib/raylib.h"
#include <memory>

void MenuState::HandleInput() {
    if (IsKeyPressed(KEY_M)) {
        startPressed = true;
    }
}

void MenuState::Draw() {
    ClearBackground(BLACK);
    DrawText("currentState: menu", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: press M to map", 0, 30, 20, WHITE);

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
    Text::Init();
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
        "New game",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            // startPressed = true;
            InitGui_newGame();
        },
        PositionType::Left
    );

    Button* btnPtr = newGameButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(GREEN);
    });
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

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
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

    buttons->Add(std::move(continueButton));

    auto modsButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Mods",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            stateMachine->ChangeState(std::make_unique<SceneState>(10.0f, [] () {
                printf("pizda");
            }));
        },
        PositionType::Left
    );

    btnPtr = modsButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(GREEN);
    });
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

    buttons->Add(std::move(modsButton));

    _gui.Add(std::move(buttons));
}

void MenuState::InitGui_newGame() 
{
    _gui.Clear();
    auto buttons = std::make_unique<ButtonList>();
    buttons->SetPosition({200, 300});
    buttons->SetIndex(1);

    /**
     * TITLE
     * 
     */

    auto chooseModeLabel = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Pls choose your gamemode:",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            
        },
        PositionType::Left
    );

    Button* btnPtr = chooseModeLabel.get();

    // btnPtr->SetOnTouch([btnPtr]() {
    //     btnPtr->SetTextColor(GREEN);
    // });
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

    buttons->Add(std::move(chooseModeLabel));

    /**
     * gamemode "Normal"
     * 
     */

     auto normalModeButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Normal",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            startPressed = true;
        },
        PositionType::Left
    );

    btnPtr = normalModeButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(GREEN);
    });
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

    buttons->Add(std::move(normalModeButton));

    /**
     * gamemode "expert"
     * 
     */

     auto expertModeButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Expert",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            startPressed = true;
        },
        PositionType::Left
    );

    btnPtr = expertModeButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(DARKBLUE);
    });
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

    buttons->Add(std::move(expertModeButton));

    /**
     * gamemode "master"
     * 
     */

     auto masterModeButton = std::make_unique<Button>(
        Vector2{150, 300},
        Vector2{300, 50},
        "Master",
        &Game::GetResources().Get("blackButton"),
        [this]() {
            //  stateMachine->ChangeState(std::make_unique<MapState>());
            startPressed = true;
        },
        PositionType::Left
    );

    btnPtr = masterModeButton.get();

    btnPtr->SetOnTouch([btnPtr]() {
        btnPtr->SetTextColor(RED);
    });
    // for non-mouse action
    btnPtr->GetSprite().SetRectSize({0, 0});

    buttons->Add(std::move(masterModeButton));

    /**
     * END
     * 
     */
    _gui.Add(std::move(buttons));

}



// void MenuState::InitGui() {
//     std::vector<TextureID> names = { TextureID::GuiNewGameButton, TextureID::GuiContinueButton, TextureID::GuiTradesButton };

//     // 150 - screen start pos
    
//     auto menuBackground = std::make_unique<Gui>();

//     Gui* bg = menuBackground.get();
//     bg->SetResource(&Game::GetResources().Get(TextureID::MenuBackground));
//     bg->SetPosition({400, 300});

//     _gui.Add(std::move(menuBackground));

//     auto newGameButton = std::make_unique<Button>(
//         Vector2{150, 300},
//         Vector2{300, 50},
//         "New game",
//         &Game::GetResources().Get(names[0]),
//         [this]() {
//             //  stateMachine->ChangeState(std::make_unique<MapState>());
//             startPressed = true;
//         }
//     );

//     // EXAMPLE OF BUTTON MANIPULATION:
//     // Button* btnPtr = newGameButton.get();

//     // btnPtr->SetOnTouch([btnPtr]() {
//     //     btnPtr->GetSprite().SetBrightness(1.5f);
//     // });

//     _gui.Add(std::move(newGameButton));


//     _gui.Add(std::make_unique<Button>(
//         Vector2{150, 360}, // y+60
//         Vector2{300, 50},
//         "Continue",
//         &Game::GetResources().Get(names[1]),
//         [this]() {
//              // stub
//         }
//     ));

//     _gui.Add(std::make_unique<Button>(
//         Vector2{150, 420}, // y+60
//         Vector2{300, 50},
//         "Trades",
//         &Game::GetResources().Get(names[2]),
//         [this]() {
//              // stub
//         }
//     ));

     
// }
