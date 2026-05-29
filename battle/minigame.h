/**
 * @file minigame.h
 * @author askar102
 * @brief Deltarune-style timing minigame — press the key when cursor hits the hole
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #pragma once
 
 #include <functional>
  
 #include "../raylib/raylib.h"

 #include "../entities/spriteV2.h"
  
 // Состояния миниигры
 enum class MinigameState {
     Idle,       // не активна
     Waiting,    // ждём нажатия клавиши-активатора (например R во время способности)
     Active,     // курсор движется, игрок должен нажать пробел
     Result      // показываем результат короткое время, потом Idle
 };
  
 class Minigame {
 public:
     // ──────────────────────────────────────────────
     //  Настройки (менять до Play())
     // ──────────────────────────────────────────────
  
     // Ширина всей полоски (px)
     float barWidth      = 160.0f;
     // Высота полоски
     float barHeight     = 18.0f;
     // Ширина "дырки" (зоны успеха)
     float holeWidth     = 4.0f;
     // Смещение центра дырки от левого края полоски (0..1, дефолт — середина)
     float holeRelativeX = 0.3f;
     // Скорость курсора (px/s)
     float cursorSpeed   = 180.0f;

    float barLifetimeTimer = 0.0f;
    float barLifetime = 0.5f;

     // Сколько секунд показывать результат
     float resultDuration = 0.6f;
     // Клавиша подтверждения внутри миниигры
     KeyboardKey confirmKey = KEY_R;
     // Смещение миниигры от позиции персонажа (вниз)
     Vector2 offset = {0.0f, 80.0f};
  
     // ──────────────────────────────────────────────
     //  API
     // ──────────────────────────────────────────────
    
    void Init();

     // Переводит в Waiting — игрок ещё может нажать activateKey чтобы запустить
     // activateKey — клавиша которую нужно нажать ПОКА идёт анимация (например R)
     // onSuccess/onFail — вызываются после того как игрок нажал confirmKey
     void Arm(KeyboardKey activateKey,
              std::function<void()> onSuccess = nullptr,
              std::function<void()> onFail    = nullptr);
  
     // Напрямую запустить активную фазу (без Waiting)
     void Play(std::function<void()> onSuccess = nullptr,
               std::function<void()> onFail    = nullptr);
  
     void Update(float dt);
  
     // anchorPos — позиция спрайта персонажа (центр)
     void Draw(SpriteV2& unit);
  
     bool IsActive()  const { return _state == MinigameState::Active;  }
     bool IsWaiting() const { return _state == MinigameState::Waiting; }
     bool IsIdle()    const { return _state == MinigameState::Idle;    }
  
     // Принудительно остановить (например если способность прервана)
     void Reset();
  
 private:
     MinigameState _state = MinigameState::Idle;
  
     float _cursorX      = 0.0f;   // текущая X позиция курсора внутри бара (0..barWidth)
     float _cursorDir    = 1.0f;   // направление движения (+1 / -1)
  
     float _resultTimer  = 0.0f;
     bool  _lastSuccess  = false;
  
     KeyboardKey _activateKey = KEY_R;
  
     std::function<void()> _onSuccess;
     std::function<void()> _onFail;
  
     // helpers
     bool CursorInHole() const;
     void FireResult();
     float HoleLeft()  const;   // левый край дырки в координатах бара
     float HoleRight() const;   // правый край дырки в координатах бара

     SpriteV2 _bgSprite;
     TextureResource _bgTex;

     SpriteV2 _holeSprite;
     SpriteV2 _cursorSrite;
 };
  
 