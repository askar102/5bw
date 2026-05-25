/**
 * @file mapEntity.h
 * @author askar102
 * @brief Base class for all map entities (visual sprite + separate hitbox sprite)
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #pragma once
 
 #include "spriteV2.h"
  
 class MapEntity {
 public:
     MapEntity() = default;
     virtual ~MapEntity() = default;
  
     // Визуальный спрайт (хитбокс у него отключён всегда)
     SpriteV2& GetVisual();
     const SpriteV2& GetVisual() const;
  
     // Хитбокс-спрайт (отдельный, невидимый, только для коллизий)
     SpriteV2& GetHitbox();
     const SpriteV2& GetHitbox() const;
     // Позиция — двигает оба спрайта сразу
     virtual void SetPosition(Vector2 position);
     Vector2 GetPosition() const;
  
     // Коллизия делегируется хитбокс-спрайту
     bool IsCollide() const;
     void SetCollide(bool value);
  
     Rectangle GetRect() const;
  
     virtual void Draw();
  
     virtual void Update(float dt) {}
  
 protected:
     SpriteV2 _visual;
     SpriteV2 _hitbox;
  
     // Смещение хитбокса относительно позиции сущности
     Vector2 _hitboxOffset{0.0f, 0.0f};
 };
  
 