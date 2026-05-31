/**
 * @file uniqueHitbox.h
 * @author askar102
 * @brief This is a entity with separate hitbox sprite
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #pragma once
 
 #include "spriteV2.h"
  
 class UniqueHitbox {
 public:
    UniqueHitbox() = default;
     virtual ~UniqueHitbox() = default;
    
     // visual sprite
     SpriteV2& GetVisual();
     const SpriteV2& GetVisual() const;

     // his hitbox
     SpriteV2& GetHitbox();
     const SpriteV2& GetHitbox() const;
     

     virtual void SetPosition(Vector2 position);
     Vector2 GetPosition() const;
  
     bool IsCollide() const;
     void SetCollide(bool value);
  
     Rectangle GetRect() const;
  
     virtual void Draw();
  
     virtual void Update(float dt) {}
  
 protected:
     SpriteV2 _visual;
     SpriteV2 _hitbox;
  
     Vector2 _hitboxOffset{0.0f, 0.0f};
 };
  
 