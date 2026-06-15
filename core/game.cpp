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
 PlayerParty Game::_playerParty;

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
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(_screenWidth, _screenHeight, _windowTitle);
    SetTargetFPS(60);

    _renderTarget = LoadRenderTexture(_virtualW, _virtualH);
    // TEXTURE_FILTER_BILINEAR
    SetTextureFilter(_renderTarget.texture, TEXTURE_FILTER_POINT);

    SpriteV2::LoadBrightnessShader();
 
    _resourceManager.Load();
 
    _stateMachine.ChangeState(std::make_unique<MenuState>());

 }
 
 void Game::Run() 
 {
     Init();
     // Init only here
     _playerParty.Init();
     NpcManager::Init();
 
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

 Vector2 Game::GetWorldMouse()
 {
     int realW = GetScreenWidth();
     int realH = GetScreenHeight();

     // todo: fix to variables, hardcore
     float scale = std::min((float)realW / 640, (float)realH / 480);
     float offsetX = (realW - 640 * scale) / 2.0f;
     float offsetY = (realH - 480 * scale) / 2.0f;
 
     Vector2 mouse = GetMousePosition();
     return {
         (mouse.x - offsetX) / scale,
         (mouse.y - offsetY) / scale
     };
 }
 
 void Game::Draw() 
{
    BeginTextureMode(_renderTarget);
        ClearBackground(BLACK);
        _stateMachine.Draw();
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);

        int realW = GetScreenWidth();
        int realH = GetScreenHeight();
        float scale = std::min((float)realW / _virtualW, (float)realH / _virtualH);
        float offsetX = (realW - _virtualW * scale) / 2.0f;
        float offsetY = (realH - _virtualH * scale) / 2.0f;

        DrawTexturePro(
            _renderTarget.texture,
            { 0, 0, (float)_virtualW, -(float)_virtualH },
            { offsetX, offsetY, _virtualW * scale, _virtualH * scale },
            { 0, 0 },
            0.0f,
            WHITE
        );
    EndDrawing();
}
 
 void Game::Shutdown() 
 {
    SpriteV2::UnloadBrightnessShader();
     Game::GetResources().Unload();
     UnloadRenderTexture(_renderTarget);

     NpcManager::Clear();

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
 
PlayerParty& Game::GetPlayerParty()
 {
    return _playerParty;
 }

