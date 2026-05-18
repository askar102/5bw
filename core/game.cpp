/**
 * @file game.cpp
 * @author askar102
 * @brief Initializing and creating a game window
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #include "game.h"

#include "../battle/party.h"

 #include "../states/menuState.h"
 
 ResourceManager Game::_resourceManager;
 Party Game::_playerParty;
 
 Game::Game(int width, int height, const char* title)
     : _screenWidth(width),
       _screenHeight(height),
       _windowTitle(title),
       _running(true) 
 {}
 
 Game::~Game() 
 {
     Shutdown();
 }
 
 void Game::Init() 
 {
    TraceLog(LOG_INFO, "[core] Creating window BLYAT :( .....");
     InitWindow(_screenWidth, _screenHeight, _windowTitle);
     SetTargetFPS(60);
 
     _resourceManager.Load();
 
     _stateMachine.ChangeState(std::make_unique<MenuState>());
 }
 
 void Game::Run() 
 {
     Init();
 
     while (!WindowShouldClose() && _running) 
     {
         Update();
         Draw();
     }
 }
 
 void Game::Update() 
 {
     float dt = GetFrameTime();
 
     _stateMachine.HandleInput();
     _stateMachine.Update(dt);
 }
 
 void Game::Draw() 
 {
     BeginDrawing();
     ClearBackground(RAYWHITE);
 
     _stateMachine.Draw();
 
     EndDrawing();
 }
 
 void Game::Shutdown() 
 {
     Game::GetResources().Unload();
     CloseWindow();
 }
 
 void Game::ChangeState(std::unique_ptr<State> newState) 
 {
     _stateMachine.ChangeState(std::move(newState));
 }
 
 ResourceManager& Game::GetResources()
 {
     return _resourceManager;
 }
 
 Party& Game::GetPlayerParty()
 {
    return _playerParty;
 }