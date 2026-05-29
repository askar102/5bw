/**
 * @file sceneState.h
 * @author askar102
 * @brief 3D billboard scene — shows a BattleEntity in a white room
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #pragma once

 #include <functional>
 #include <memory>
 
 #include "../raylib/raylib.h"
 #include "../raylib/raymath.h"   // Vector3Add и т.д.
 
 #include "../core/state.h"
 #include "../core/game.h"
 #include "../battle/battleEntity.h"
 
 // ─────────────────────────────────────────────────────────────
 //  Настройки камеры по умолчанию
 // ─────────────────────────────────────────────────────────────
 struct SceneCameraConfig {
     Vector3 position  = { 0.0f, 2.5f, 6.0f };  // откуда смотрит камера
     Vector3 target    = { 0.0f, 1.5f, 0.0f };  // куда смотрит
     float   fovy      = 45.0f;
     // зум мышкой
     float   zoomSpeed = 2.0f;
     float   minDist   = 2.0f;
     float   maxDist   = 20.0f;
     // перемещение мышкой (ПКМ + drag)
     float   panSpeed  = 0.005f;
 };
 
 // ─────────────────────────────────────────────────────────────
 //  SceneState
 // ─────────────────────────────────────────────────────────────
 class SceneState : public State {
 public:
     // duration   — секунды до автозавершения (<=0 — только ручной вызов Finish())
     // onFinish   — вызывается когда сцена заканчивается (переход обратно)
     // camCfg     — можно переопределить положение камеры
     explicit SceneState(float                    duration,
                         std::function<void()>    onFinish,
                         BattleEntity*            entity   = nullptr,
                         SceneCameraConfig        camCfg   = {});
 
     // ── State interface ──────────────────────────────────────
     void OnEnter()      override;
     void OnExit()       override;
     void HandleInput()  override;
     void Update(float dt) override;
     void Draw()         override;
 
     // ── API ──────────────────────────────────────────────────
 
     // Поставить/сменить персонажа уже после создания стейта
     void SetEntity(BattleEntity* entity) { _entity = entity; }
 
     // Принудительно завершить сцену
     void Finish();
 
 private:
     // ── helpers ──────────────────────────────────────────────
     void DrawRoom()      const;
     void DrawCharacter() const;
     void UpdateCamera(float dt);
 
     // ── data ─────────────────────────────────────────────────
     float                   _duration;      // <=0 → бесконечно
     float                   _elapsed = 0.0f;
     std::function<void()>   _onFinish;
     bool                    _finished = false;
 
     BattleEntity*           _entity   = nullptr;
 
     Camera3D                _camera   = {};
     SceneCameraConfig       _camCfg;
 
     // drag-pan state
     Vector2                 _lastMouse = {};
     bool                    _dragging  = false;
 
     // размер billboard (подгоняем под размер спрайта)
     static constexpr float  BILLBOARD_SCALE = 0.018f; // px → world units
 };