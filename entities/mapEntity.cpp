/**
 * @file mapEntity.cpp
 * @author askar102
 * @brief Base class for all map entities (visual sprite + separate hitbox sprite)
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */
 
 #include "mapEntity.h"

 SpriteV2& MapEntity::GetVisual()
 {
     return _visual;
 }
  
 const SpriteV2& MapEntity::GetVisual() const
 {
     return _visual;
 }
  
 SpriteV2& MapEntity::GetHitbox()
 {
     return _hitbox;
 }
  
 const SpriteV2& MapEntity::GetHitbox() const
 {
     return _hitbox;
 }
  
 void MapEntity::SetPosition(Vector2 position)
 {
     _visual.SetPosition(position);
  
     _hitbox.SetPosition({
         position.x + _hitboxOffset.x,
         position.y + _hitboxOffset.y
     });
 }
  
 Vector2 MapEntity::GetPosition() const
 {
     return _visual.GetPosition();
 }
  
 bool MapEntity::IsCollide() const
 {
     return _hitbox.IsCollide();
 }
  
 void MapEntity::SetCollide(bool value)
 {
     _hitbox.SetCollide(value);
 }
  
 Rectangle MapEntity::GetRect() const
 {
     return _hitbox.GetRect();
 }
  
 void MapEntity::Draw()
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
