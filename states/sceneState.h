/**
 * @file sceneState.h
 * @author askar102
 * @brief 3D billboard scene with per-frame script callback
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #pragma once

 #include <functional>
 #include <memory>
 
 #include "../raylib/raylib.h"
 #include "../raylib/raymath.h"
 
 #include "../core/state.h"
 #include "../core/game.h"
 #include "../battle/battleEntity.h"
 

 struct SceneCameraConfig {
     Vector3 position  = { 0.0f, 2.5f, 6.0f };
     Vector3 target    = { 0.0f, 1.5f, 0.0f };
     float   fovy      = 45.0f;
     float   zoomSpeed = 2.0f;
     float   minDist   = 2.0f;
     float   maxDist   = 20.0f;
     float   panSpeed  = 0.005f;
 };
 
 class SceneState;
 

 struct SceneContext {
     float         elapsed;
     float         dt;        
     Camera3D&     camera;    
     BattleEntity* entity;    
     SceneState&   scene;     
 };
 

 class SceneState : public State {
 public:
     explicit SceneState(float                              duration,
                         std::function<void()>              onFinish,
                         std::function<void(SceneContext&)> onUpdate  = nullptr,
                         BattleEntity*                      entity    = nullptr,
                         SceneCameraConfig                  camCfg    = {});
 

     void OnEnter()        override;
     void OnExit()         override;
     void HandleInput()    override;
     void Update(float dt) override;
     void Draw()           override;
 

     void SetEntity(BattleEntity* entity) { _entity = entity; }

     void Finish();
 
 private:
     void DrawRoom()           const;
     void DrawCharacter()      const;
     void UpdateCamera(float dt);
 
     float                              _duration;
     float                              _elapsed  = 0.0f;
     std::function<void()>              _onFinish;
     std::function<void(SceneContext&)> _onUpdate;
     bool                               _finished = false;
 
     BattleEntity*   _entity = nullptr;
     Camera3D        _camera = {};
     SceneCameraConfig _camCfg;
 
     Vector2 _lastMouse = {};
     bool    _dragging  = false;
 
     static constexpr float BILLBOARD_SCALE = 0.018f;
 };