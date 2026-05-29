/**
 * @file sceneState.cpp
 * @author askar102
 * @brief 3D billboard scene — shows a BattleEntity in a white room
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "sceneState.h"
 #include "../core/stateManager.h"
 
 // ─────────────────────────────────────────────────────────────
 //  Ctor
 // ─────────────────────────────────────────────────────────────
 SceneState::SceneState(float                 duration,
                        std::function<void()> onFinish,
                        BattleEntity*         entity,
                        SceneCameraConfig     camCfg)
     : _duration(duration),
       _onFinish(std::move(onFinish)),
       _entity(entity),
       _camCfg(camCfg)
 {}
 
 // ─────────────────────────────────────────────────────────────
 //  State lifecycle
 // ─────────────────────────────────────────────────────────────
 void SceneState::OnEnter()
 {
     _elapsed  = 0.0f;
     _finished = false;
 
     // Инициализируем Camera3D
     _camera.position   = _camCfg.position;
     _camera.target     = _camCfg.target;
     _camera.up         = { 0.0f, 1.0f, 0.0f };
     _camera.fovy       = _camCfg.fovy;
     _camera.projection = CAMERA_PERSPECTIVE;
 }
 
 void SceneState::OnExit()
 {
     // ничего освобождать не надо — текстуры живут в ResourceManager
 }
 
 // ─────────────────────────────────────────────────────────────
 //  Input
 // ─────────────────────────────────────────────────────────────
 void SceneState::HandleInput()
 {
     // Ничего особенного — камера обновляется в Update
 }
 
 // ─────────────────────────────────────────────────────────────
 //  Update
 // ─────────────────────────────────────────────────────────────
 void SceneState::Update(float dt)
 {
     if (_finished) return;
 
     // Обновляем сущность (шейкинг, альфа-флэш, анимации и т.д.)
     if (_entity)
         _entity->Update(dt);
 
     // Камера
     UpdateCamera(dt);
 
     // Таймер автозавершения
     if (_duration > 0.0f)
     {
         _elapsed += dt;
         if (_elapsed >= _duration)
             Finish();
     }
 }
 
 // ─────────────────────────────────────────────────────────────
 //  Draw
 // ─────────────────────────────────────────────────────────────
 void SceneState::Draw()
 {
     ClearBackground(WHITE);
 
     BeginMode3D(_camera);
         DrawRoom();
         DrawCharacter();
     EndMode3D();
 
     // 2D HUD поверх — таймер обратного отсчёта
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
 
 // ─────────────────────────────────────────────────────────────
 //  Finish
 // ─────────────────────────────────────────────────────────────
 void SceneState::Finish()
 {
     if (_finished) return;
     _finished = true;
 
     if (_onFinish)
         _onFinish();
 }
 
 // ─────────────────────────────────────────────────────────────
 //  DrawRoom  — белая комната
 // ─────────────────────────────────────────────────────────────
 void SceneState::DrawRoom() const
 {
     const Color wallColor  = WHITE;
     const Color floorColor = { 230, 230, 230, 255 }; // чуть серее чтобы был контраст
 
     // Пол
     DrawPlane({ 0.0f, 0.0f, 0.0f }, { 20.0f, 20.0f }, floorColor);
 
     // Задняя стена
     DrawCube({ 0.0f, 5.0f, -10.0f }, 20.0f, 10.0f, 0.2f, wallColor);
 
     // Левая стена
     DrawCube({ -10.0f, 5.0f, 0.0f }, 0.2f, 10.0f, 20.0f, wallColor);
 
     // Правая стена
     DrawCube({  10.0f, 5.0f, 0.0f }, 0.2f, 10.0f, 20.0f, wallColor);
 
     // Потолок
     DrawCube({ 0.0f, 10.0f, 0.0f }, 20.0f, 0.2f, 20.0f, wallColor);
 
     // Рёбра / плинтусы — тонкие серые линии чтобы углы читались
     const Color edge = { 180, 180, 180, 255 };
     // пол-задняя
     DrawCube({ 0.0f, 0.05f, -10.0f }, 20.0f, 0.1f, 0.1f, edge);
     // пол-лево
     DrawCube({ -10.0f, 0.05f, 0.0f }, 0.1f, 0.1f, 20.0f, edge);
     // пол-право
     DrawCube({  10.0f, 0.05f, 0.0f }, 0.1f, 0.1f, 20.0f, edge);
 }
 
 // ─────────────────────────────────────────────────────────────
 //  DrawCharacter  — billboard в центре комнаты
 // ─────────────────────────────────────────────────────────────
 void SceneState::DrawCharacter() const
 {
     if (!_entity) return;
 
     SpriteV2& spr = _entity->getSprite();
 
     // Получаем текстуру и текущий фрейм из SpriteV2
     // SpriteV2 не даёт прямого доступа к _resource/_frame,
     // поэтому достаём их через ResourceManager по имени персонажа
     // (текстура уже загружена, просто берём ссылку)
     TextureResource* res = nullptr;
     {
         // Пробуем сначала через имя (кастомные текстуры: cardGuy, angryGuy, ...)
         // ResourceManager::Get(string) уже кэширует, так что без двойной загрузки
         res = &Game::GetResources().Get(_entity->name);
     }
 
     if (!res || res->texture.id == 0) return;
 
     // Шейкинг: берём _shakeOffset через Update — он уже посчитан в SpriteV2::Update.
     // Мы не имеем прямого доступа к _shakeOffset, но он влияет на GetPosition().
     // Поэтому просто используем позицию спрайта как delta и игнорируем его 2D coords —
     // нам нужен только шейк. Трюк: сравниваем GetPosition() с "чистой" позицией.
     // Но проще — добавить геттер в SpriteV2. Пока делаем через дельту от startPosition.
     //
     // NOTE: добавь в SpriteV2 геттер:
     //   Vector2 GetShakeOffset() const { return _shakeOffset; }
     // Тогда можно будет написать:
    //    Vector2 shake = spr.GetShakeOffset();
     // А пока shake = {0,0} и шейкинг читается через SpriteV2::Draw() в 2D поверх.
 
     // Billboard позиция — центр комнаты, чуть над полом
     Vector3 billboardPos = { 0.0f, 1.5f, 0.0f };
 
     // Шейкинг: если добавишь GetShakeOffset() в SpriteV2 — раскомментируй:
     Vector2 shake = spr.GetShakeOffset();
     billboardPos.x += shake.x * BILLBOARD_SCALE * 10.0f;
     billboardPos.y += shake.y * BILLBOARD_SCALE * 10.0f;
 
     // Размер billboard в world units
     Vector2 sprSize = spr.GetSize();
     Vector2 billSize = {
         sprSize.x * BILLBOARD_SCALE,
         sprSize.y * BILLBOARD_SCALE
     };
 
     // Выбираем нужный фрейм (atlas или полная текстура)
     if (!res->frames.empty())
     {
         // Атлас — DrawBillboardRec
         // Текущий фрейм не доступен снаружи напрямую, но SpriteV2::GetRect()
         // возвращает hitbox, не source. Добавь геттер GetSourceRect():
         //   Rectangle GetSourceRect() const { return _frame; }
         // Пока берём фрейм 0 как заглушку:
         Rectangle srcRect = spr.GetSourceRect(); 
 
         // Если добавишь GetSourceRect():
         // Rectangle srcRect = spr.GetSourceRect();
 
         DrawBillboardRec(
             _camera,
             res->texture,
             srcRect,
             billboardPos,
             billSize,
             WHITE
         );
     }
     else
     {
         // Полная текстура
         DrawBillboard(
             _camera,
             res->texture,
             billboardPos,
             billSize.x,   // DrawBillboard принимает один float size (ширину)
             WHITE
         );
     }
 }
 
 // ─────────────────────────────────────────────────────────────
 //  UpdateCamera
 // ─────────────────────────────────────────────────────────────
 void SceneState::UpdateCamera(float dt)
 {
     (void)dt;
 
     // ── Зум колёсиком мыши ──────────────────────────────────
     float wheel = GetMouseWheelMove();
     if (wheel != 0.0f)
     {
         // Двигаем камеру вдоль вектора взгляда
         Vector3 dir = Vector3Normalize(
             Vector3Subtract(_camera.target, _camera.position)
         );
         float delta = wheel * _camCfg.zoomSpeed;
 
         // Проверяем что не проваливаемся за minDist
         float dist = Vector3Length(
             Vector3Subtract(_camera.position, _camera.target)
         );
 
         if (delta > 0 && dist - delta < _camCfg.minDist) delta = dist - _camCfg.minDist;
         if (delta < 0 && dist - delta > _camCfg.maxDist) delta = dist - _camCfg.maxDist;
 
         _camera.position = Vector3Add(
             _camera.position,
             Vector3Scale(dir, delta)
         );
     }
 
     // ── Pan — ПКМ + drag ────────────────────────────────────
     Vector2 mouse = GetMousePosition();
 
     if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
     {
         _lastMouse = mouse;
         _dragging  = true;
     }
 
     if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))
         _dragging = false;
 
     if (_dragging)
     {
         Vector2 delta = { mouse.x - _lastMouse.x, mouse.y - _lastMouse.y };
         _lastMouse = mouse;
 
         // Сдвигаем и camera.position и camera.target на одинаковый вектор
         // чтобы не менять направление взгляда
         Vector3 right = Vector3Normalize({
             _camera.target.z - _camera.position.z, // cross(forward, up).x
             0.0f,
             _camera.position.x - _camera.target.x  // cross(forward, up).z
         });
         Vector3 up = { 0.0f, 1.0f, 0.0f };
 
         Vector3 pan = Vector3Add(
             Vector3Scale(right, -delta.x * _camCfg.panSpeed),
             Vector3Scale(up,     delta.y * _camCfg.panSpeed)
         );
 
         _camera.position = Vector3Add(_camera.position, pan);
         _camera.target   = Vector3Add(_camera.target,   pan);
     }
 
     // ── Орбита — ЛКМ + drag ─────────────────────────────────
     if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
     {
         UpdateCameraPro(
             &_camera,
             { 0 },                          // движение — не используем
             { GetMouseDelta().x * 0.2f,     // yaw
               GetMouseDelta().y * 0.2f,     // pitch
               0.0f },                       // roll
             0.0f
         );
     }
 }