/**
 * @file game.h
 * @author askar102
 * @brief Initializing and creating a game window
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #pragma once

 #include <memory>
 
 #include "state.h"
 #include "stateManager.h"
 #include "resourceManager.h"
 #include "../battle/party.h"

 #include "../raylib/raylib.h"
 
 class Game {
 public:
     Game(int width, int height, const char* title);
     ~Game();
 
     void Run();
 
     void ChangeState(std::unique_ptr<State> newState);
 
     static ResourceManager& GetResources();
     static Party& GetPlayerParty();
     
 private:
     void Init();
     void Update();
     void Draw();
     void Shutdown();
 
 private:
     int _screenWidth;
     int _screenHeight;
     const char* _windowTitle;
 
     bool _running;
 
     StateManager _stateMachine;

     static ResourceManager _resourceManager;

     static Party _playerParty;
 };
 
