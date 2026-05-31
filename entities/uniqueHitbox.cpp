/**
 * @file uniqueHitbox.cpp
 * @author askar102
 * @brief This is a entity with separate hitbox sprite
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #include "uniqueHitbox.h"

 SpriteV2& UniqueHitbox::GetVisual()
 {
     return _visual;
 }
  
 const SpriteV2& UniqueHitbox::GetVisual() const
 {
     return _visual;
 }
  
 SpriteV2& UniqueHitbox::GetHitbox()
 {
     return _hitbox;
 }
  
 const SpriteV2& UniqueHitbox::GetHitbox() const
 {
     return _hitbox;
 }
  
 void UniqueHitbox::SetPosition(Vector2 position)
 {
     _visual.SetPosition(position);
  
     _hitbox.SetPosition({
         position.x + _hitboxOffset.x,
         position.y + _hitboxOffset.y
     });
 }
  
 Vector2 UniqueHitbox::GetPosition() const
 {
     return _visual.GetPosition();
 }
  
 bool UniqueHitbox::IsCollide() const
 {
     return _hitbox.IsCollide();
 }
  
 void UniqueHitbox::SetCollide(bool value)
 {
     _hitbox.SetCollide(value);
 }
  
 Rectangle UniqueHitbox::GetRect() const
 {
     return _hitbox.GetRect();
 }
  
 void UniqueHitbox::Draw()
 {
     _visual.Draw();
  
     if (SpriteV2::GetDrawHitboxes())
    {
        Rectangle r = _hitbox.GetRect();
        Vector2 origin = {r.width * 0.5f, r.height * 0.5f};

        DrawRectanglePro(
            {_hitbox.GetPosition().x, _hitbox.GetPosition().y, r.width, r.height},
            origin,
            0.0f,
            Fade(RED, 0.5f)
        );
    }
 }
