/**
 * @file minigame.cpp
 * @author askar102
 * @brief Deltarune-style timing minigame
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #include "minigame.h"
 
 // ──────────────────────────────────────────────────────────────
 //  Public API
 // ──────────────────────────────────────────────────────────────
  
void Minigame::Init()
{
    barLifetimeTimer = 0.0f;
    _bgTex = {LoadTexture("resources/minigameBackground.png"), {}};
    _bgSprite.SetResource(&_bgTex);
}

 void Minigame::Arm(KeyboardKey activateKey,
                    std::function<void()> onSuccess,
                    std::function<void()> onFail,
                    std::function<void()> onSkip,
                    float hiddenDuration)
 {
     _activateKey = activateKey;

     _onSuccess   = std::move(onSuccess);
     _onFail      = std::move(onFail);
     _onSkip      = std::move(onSkip);

    _hiddenDuration = hiddenDuration;  // <- этого не было
    _hiddenTimer    = 0.0f;            // <- и этого

     _state         = MinigameState::Hidden;

     Init();
 }
  
 void Minigame::Play(std::function<void()> onSuccess,
                     std::function<void()> onFail,
                     std::function<void()> onSkip )
 {
     _onSuccess  = std::move(onSuccess);
     _onFail     = std::move(onFail);
     _onSkip      = std::move(onSkip);

     _cursorX    = 0.0f;
     _cursorDir  = 1.0f;
     _state      = MinigameState::Active;

     barLifetimeTimer = 0.0f;

     Init();
 }
  
 void Minigame::Reset()
 {
     _state       = MinigameState::Idle;
     _onSuccess   = nullptr;
     if (_onSkip) {
        _onSkip();
     }
     _onFail      = nullptr;
     _resultTimer = 0.0f;
 }
  
 // ──────────────────────────────────────────────────────────────
 //  Update
 // ──────────────────────────────────────────────────────────────
  
 void Minigame::Update(float dt)
 {

     switch (_state)
     {
     case MinigameState::Idle:
         break;
        
    case MinigameState::Hidden:
         _hiddenTimer += dt;
     
         if (IsKeyPressed(_activateKey))
         {
             // игрок нашёл секрет — переходим в Waiting (показываем бар)
             _state = MinigameState::Waiting;
             barLifetimeTimer = 0.0f;
             break;
         }
     
         if (_hiddenTimer >= _hiddenDuration)
         {
             // время вышло, никто не нажал — тихо пропускаем в onSkip
             Reset(); // внутри вызовет _onSkip
         }
         break;

     case MinigameState::Waiting:
         // Ждём нажатия клавиши-активатора (например R)

         barLifetimeTimer += dt;

         if (barLifetimeTimer >= barLifetime)
         {
             Reset();
         }

         if (IsKeyPressed(_activateKey))
         {
             _cursorX   = barWidth;
             _cursorDir = 1.0f;
             _state     = MinigameState::Active;
         }
         break;
  
     case MinigameState::Active:
     {
         // Двигаем курсор туда-обратно
         _cursorX += _cursorDir * cursorSpeed * dt;
  
         if (_cursorX >= barWidth)
         {
             _cursorX  = barWidth;
             _cursorDir = -1.0f;
         }
         else if (_cursorX <= 0.0f)
         {
            //  _cursorX  = 0.0f;
            //  _cursorDir = 1.0f;
            FireResult();
         }
  
         // Игрок нажал confirmKey
         if (IsKeyPressed(confirmKey))
         {
             FireResult();
         }
         break;
     }
  
     case MinigameState::Result:
         _resultTimer -= dt;
         if (_resultTimer <= 0.0f)
             _state = MinigameState::Idle;
         break;
     }
 }
  
 // ──────────────────────────────────────────────────────────────
 //  Draw
 // ──────────────────────────────────────────────────────────────
  
 void Minigame::Draw(SpriteV2& unit)
 {
    if (_state == MinigameState::Idle || _state == MinigameState::Hidden)
        return;
  
     Vector2 unitPos  = unit.GetPosition();
     Vector2 unitSize = unit.GetSize();
  
     // Левый верхний угол бара — под персонажем по центру
     float barX = unitPos.x - barWidth * 0.5f;
    float barY = unitPos.y + unitSize.y * 0.5f + 10.0f;
  
    //  // ── Фон бара ──
    //  DrawRectangle(
    //      static_cast<int>(barX),
    //      static_cast<int>(barY),
    //      static_cast<int>(barWidth),
    //      static_cast<int>(barHeight),
    //      Color{30, 30, 30, 200}
    //  );

    
    

     _bgSprite.SetPosition({barX + 80.0f, barY + 15.0f});
     _bgSprite.SetSize({barWidth, barHeight});
     _bgSprite.SetAlpha(0.7f);
     _bgSprite.Draw();

  
     // ── Дырка (зона успеха) ──
     Color holeColor = Color{80, 220, 80, 230};
     DrawRectangle(
         static_cast<int>(barX + HoleLeft()),
         static_cast<int>(barY),
         static_cast<int>(holeWidth),
         static_cast<int>(barHeight),
         holeColor
     );
  
     // ── Рамка бара ──
     DrawRectangleLines(
         static_cast<int>(barX),
         static_cast<int>(barY),
         static_cast<int>(barWidth),
         static_cast<int>(barHeight),
         WHITE
     );
  
     if (_state == MinigameState::Active || _state == MinigameState::Waiting)
     {
         // ── Курсор ──
         constexpr float CURSOR_W = 4.0f;
         float cx = barX + _cursorX - CURSOR_W * 0.5f;
         DrawRectangle(
             static_cast<int>(cx),
             static_cast<int>(barY - 2),
             static_cast<int>(CURSOR_W),
             static_cast<int>(barHeight + 4),
             WHITE
         );
  
         // Подсказка: "PRESS SPACE"
         const char* hint = (_state == MinigameState::Waiting) ? "PRESS R!" : "SPACE!";
         int fontSize = 12;
         int textW    = MeasureText(hint, fontSize);
         DrawText(
             hint,
             static_cast<int>(barX + barWidth * 0.5f - textW * 0.5f),
             static_cast<int>(barY - fontSize - 4),
             fontSize,
             YELLOW
         );
     }
  
     // ── Результат ──
     if (_state == MinigameState::Result)
     {
         const char* msg   = _lastSuccess ? "NICE!" : "MISS";
         Color        col  = _lastSuccess ? GREEN   : RED;
         int fontSize = 14;
         int textW    = MeasureText(msg, fontSize);
         DrawText(
             msg,
             static_cast<int>(barX + barWidth * 0.5f - textW * 0.5f),
             static_cast<int>(barY - fontSize - 4),
             fontSize,
             col
         );
     }
 }
  
 // ──────────────────────────────────────────────────────────────
 //  Private helpers
 // ──────────────────────────────────────────────────────────────
  
 float Minigame::HoleLeft() const
 {
     float center = barWidth * holeRelativeX;
     return center - holeWidth * 0.5f;
 }
  
 float Minigame::HoleRight() const
 {
     return HoleLeft() + holeWidth;
 }
  
 bool Minigame::CursorInHole() const
 {
     return _cursorX >= HoleLeft() && _cursorX <= HoleRight();
 }
  
 void Minigame::FireResult()
 {
     _lastSuccess = CursorInHole();
     _resultTimer = resultDuration;
     _state       = MinigameState::Result;
  
     if (_lastSuccess && _onSuccess)
         _onSuccess();
     else if (!_lastSuccess && _onFail)
         _onFail();
  
     _onSuccess = nullptr;
     _onFail    = nullptr;
 }
 