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

 #include "../battle/playerParty.h"
 #include "../map/npcManager.h"

 #include "../raylib/raylib.h"

 #include "../entities/spriteV2.h"

class Party;

 class Game {
 public:
     Game(int width, int height, const char* title);
     ~Game();
 
     void Run();
 
     void ChangeState(std::unique_ptr<State> newState);
 
     static ResourceManager& GetResources();

     static PlayerParty& GetPlayerParty();

     static Vector2 GetWorldMouse();

     static Vector2 GetVirtualPos();

 private:
     void Init();
     void Update();
     void Draw();
     void Shutdown();
 
 private:
     int _screenWidth;
     int _screenHeight;
     const char* _windowTitle;

     RenderTexture2D _renderTarget;
     int _virtualW = 640; 
     int _virtualH = 480;
 
     bool _running;
 
     StateManager _stateMachine;

     static ResourceManager _resourceManager;

     static PlayerParty _playerParty;
 };
 
