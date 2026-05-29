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
 
 // ─────────────────────────────────────────────────────────────
 //  Настройки камеры
 // ─────────────────────────────────────────────────────────────
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
 
 // ─────────────────────────────────────────────────────────────
 //  SceneContext — то что получает onUpdate каждый кадр
 // ─────────────────────────────────────────────────────────────
 struct SceneContext {
     float         elapsed;   // сколько прошло с начала сцены (секунды)
     float         dt;        // delta time этого кадра
     Camera3D&     camera;    // камера — двигай, зумь, крути
     BattleEntity* entity;    // персонаж — SetShaking, SetFrame и т.д. (может быть nullptr)
     SceneState&   scene;     // сам стейт — можно вызвать Finish() чтобы закрыть раньше
 };
 
 // ─────────────────────────────────────────────────────────────
 //  SceneState
 // ─────────────────────────────────────────────────────────────
 class SceneState : public State {
 public:
     // duration   — секунды до автозавершения (<=0 — только через Finish())
     // onFinish   — вызывается перед PopState
     // onUpdate   — вызывается каждый кадр, получает SceneContext
     // entity     — персонаж на сцене (можно nullptr)
     // camCfg     — начальное положение камеры
     explicit SceneState(float                              duration,
                         std::function<void()>              onFinish,
                         std::function<void(SceneContext&)> onUpdate  = nullptr,
                         BattleEntity*                      entity    = nullptr,
                         SceneCameraConfig                  camCfg    = {});
 
     // ── State interface ──────────────────────────────────────
     void OnEnter()        override;
     void OnExit()         override;
     void HandleInput()    override;
     void Update(float dt) override;
     void Draw()           override;
 
     // ── API ──────────────────────────────────────────────────
     void SetEntity(BattleEntity* entity) { _entity = entity; }
 
     // Принудительно завершить сцену → onFinish() → PopState()
     void Finish();
 
 private:
     void DrawRoom()           const;
     void DrawCharacter()      const;
     void UpdateCamera(float dt);
 
     // ── data ─────────────────────────────────────────────────
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