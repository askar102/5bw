/**
 * @file sceneState.cpp
 * @author askar102
 * @brief 3D billboard scene with per-frame script callback
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "sceneState.h"
 #include "../core/stateManager.h"
 

 SceneState::SceneState(float                              duration,
                        std::function<void()>              onFinish,
                        std::function<void(SceneContext&)> onUpdate,
                        BattleEntity*                      entity,
                        SceneCameraConfig                  camCfg)
     : _duration(duration),
       _onFinish(std::move(onFinish)),
       _onUpdate(std::move(onUpdate)),
       _entity(entity),
       _camCfg(camCfg)
 {}
 

 void SceneState::OnEnter()
 {
     _elapsed  = 0.0f;
     _finished = false;
 
     _camera.position   = _camCfg.position;
     _camera.target     = _camCfg.target;
     _camera.up         = { 0.0f, 1.0f, 0.0f };
     _camera.fovy       = _camCfg.fovy;
     _camera.projection = CAMERA_PERSPECTIVE;
 }
 
 void SceneState::OnExit() {}
 
 void SceneState::HandleInput() {}
 

 void SceneState::Update(float dt)
 {
     if (_finished) return;
 
     _elapsed += dt;
 
     if (_entity)
         _entity->Update(dt);
 
     if (_onUpdate)
     {
         SceneContext ctx {
             _elapsed,
             dt,
             _camera,
             _entity,
             *this
         };
         _onUpdate(ctx);
     }
 
     UpdateCamera(dt);
 
     if (_duration > 0.0f && _elapsed >= _duration)
         Finish();
 }
 
 void SceneState::Draw()
 {
     ClearBackground(WHITE);
 
     BeginMode3D(_camera);
         DrawRoom();
         DrawCharacter();
     EndMode3D();
 
     if (_duration > 0.0f)
     {
         float remaining = _duration - _elapsed;
         DrawText(
             TextFormat("%.1f", remaining),
             GetScreenWidth() - 60, 10,
             24, DARKGRAY
         );
     }
 }

 void SceneState::Finish()
 {
     if (_finished) return;
     _finished = true;
 
     if (_onFinish)
         _onFinish();
 
     if (stateMachine)
         stateMachine->PopState();
 }

 void SceneState::DrawRoom() const
 {
     const Color wallColor  = WHITE;
     const Color floorColor = { 230, 230, 230, 255 };
     const Color edge       = { 180, 180, 180, 255 };
 
     DrawPlane({ 0.0f, 0.0f, 0.0f }, { 20.0f, 20.0f }, floorColor);
     DrawCube({ 0.0f,   5.0f, -10.0f }, 20.0f, 10.0f, 0.2f,  wallColor);
     DrawCube({ -10.0f, 5.0f,  0.0f  }, 0.2f,  10.0f, 20.0f, wallColor);
     DrawCube({  10.0f, 5.0f,  0.0f  }, 0.2f,  10.0f, 20.0f, wallColor);
     DrawCube({ 0.0f,  10.0f,  0.0f  }, 20.0f, 0.2f,  20.0f, wallColor);
 
     DrawCube({ 0.0f,   0.05f, -10.0f }, 20.0f, 0.1f, 0.1f, edge);
     DrawCube({ -10.0f, 0.05f,  0.0f  }, 0.1f,  0.1f, 20.0f, edge);
     DrawCube({  10.0f, 0.05f,  0.0f  }, 0.1f,  0.1f, 20.0f, edge);
 }
 

 void SceneState::DrawCharacter() const
 {
     if (!_entity) return;
 
     SpriteV2& spr = _entity->getSprite();
     TextureResource* res = &Game::GetResources().Get(_entity->name);
     if (!res || res->texture.id == 0) return;

     Vector3 billboardPos = { 0.0f, 1.5f, 0.0f };
 
     Vector2 shake = spr.GetShakeOffset();
     billboardPos.x += shake.x * BILLBOARD_SCALE * 10.0f;
     billboardPos.y -= shake.y * BILLBOARD_SCALE * 10.0f; 
 
     Vector2 sprSize  = spr.GetSize();
     Vector2 billSize = { sprSize.x * BILLBOARD_SCALE, sprSize.y * BILLBOARD_SCALE };
 
     if (!res->frames.empty())
     {
         Rectangle srcRect = spr.GetSourceRect();
         DrawBillboardRec(_camera, res->texture, srcRect, billboardPos, billSize, WHITE);
     }
     else
     {
         DrawBillboard(_camera, res->texture, billboardPos, billSize.x, WHITE);
     }
 }
 
 void SceneState::UpdateCamera(float dt)
 {
     (void)dt;

     float wheel = GetMouseWheelMove();
     if (wheel != 0.0f)
     {
         Vector3 dir  = Vector3Normalize(Vector3Subtract(_camera.target, _camera.position));
         float   dist = Vector3Length(Vector3Subtract(_camera.position, _camera.target));
         float   delta = wheel * _camCfg.zoomSpeed;
 
         if (delta > 0 && dist - delta < _camCfg.minDist) delta = dist - _camCfg.minDist;
         if (delta < 0 && dist - delta > _camCfg.maxDist) delta = dist - _camCfg.maxDist;
 
         _camera.position = Vector3Add(_camera.position, Vector3Scale(dir, delta));
     }
 
     Vector2 mouse = GetMousePosition();
 
     if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))  { _lastMouse = mouse; _dragging = true;  }
     if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))   _dragging = false;
 
     if (_dragging)
     {
         Vector2 delta = { mouse.x - _lastMouse.x, mouse.y - _lastMouse.y };
         _lastMouse = mouse;
 
         Vector3 right = Vector3Normalize({
             _camera.target.z - _camera.position.z,
             0.0f,
             _camera.position.x - _camera.target.x
         });
         Vector3 up = { 0.0f, 1.0f, 0.0f };
 
         Vector3 pan = Vector3Add(
             Vector3Scale(right, -delta.x * _camCfg.panSpeed),
             Vector3Scale(up,     delta.y * _camCfg.panSpeed)
         );
         _camera.position = Vector3Add(_camera.position, pan);
         _camera.target   = Vector3Add(_camera.target,   pan);
     }
 
     // control
     if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
     {
         UpdateCameraPro(
             &_camera,
             { 0 },
             { GetMouseDelta().x * 0.2f, GetMouseDelta().y * 0.2f, 0.0f },
             0.0f
         );
     }
 }