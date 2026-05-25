/**
 * @file sprite.cpp
 * @author askar102
 * @brief Sprite type
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #include "spriteV2.h"

 bool SpriteV2::_drawHitboxes = false;
 
 Shader SpriteV2::_brightnessShader = {};
 int SpriteV2::_brightnessLoc = 0;
 bool SpriteV2::_shaderLoaded = false;

 /**
  * 
  * Resources
  * 
  */
 
 void SpriteV2::SetResource(TextureResource* newResource)
 {
     _resource = newResource;
     _frameIndex = 0;
 
     if (!HasResource())
     {
         _frame = {0.0f, 0.0f, 0.0f, 0.0f};
         _size = {0.0f, 0.0f};
         _rect.width = 0.0f;
         _rect.height = 0.0f;
         
         return;
     }
 
     if (HasAtlas())
     {
         _frame = _resource->frames[0];
     }
     else
     {
         _frame = {
             0.0f,
             0.0f,
             static_cast<float>(_resource->texture.width),
             static_cast<float>(_resource->texture.height)
         };
     }
 
     SyncSizeWithSource();
 }
 
 /**
  * 
  * Visual
  * 
  */
 
 Vector2 SpriteV2::GetPosition() const
 {
     return _position;
 }
 
 void SpriteV2::SetPosition(Vector2 newPosition)
 {
     _position = newPosition;
 }
 
 Vector2 SpriteV2::GetSize() const
 {
     return _size;
 }
 
 void SpriteV2::SetSize(Vector2 newSize)
 {
     _size = newSize;
     _rect.width = _size.x;
     _rect.height = _size.y;
 }
 
 float SpriteV2::GetRotation() const
 {
     return _rotation;
 }
 
 void SpriteV2::SetRotation(float newRotation)
 {
     _rotation = newRotation;
 }
 

/**
 * effects
 * 
 *  
 */

 // alpha
 float SpriteV2::GetAlpha() const
 {
     return _alpha;
 }
 
 void SpriteV2::SetAlpha(float newAlpha)
 {
     _alpha = newAlpha;
 }

 // brightness
 void SpriteV2::LoadBrightnessShader()
 {
     _brightnessShader = LoadShader(nullptr, "resources/shaders/brightness.fs");
     _brightnessLoc = GetShaderLocation(_brightnessShader, "brightness");
     _shaderLoaded = true;
 }
 
 void SpriteV2::UnloadBrightnessShader()
 {
     if (_shaderLoaded)
         UnloadShader(_brightnessShader);
     _shaderLoaded = false;
 }
 
 float SpriteV2::GetBrightness() const { return _brightness; }
 
 void SpriteV2::SetBrightness(float newBrightness) { _brightness = newBrightness; }

 
 /**
  * 
  * Atlas
  *
  */
 
 void SpriteV2::SetFrame(size_t index)
 {
     if (!HasAtlas())
     {
         return;
     }
 
     if (index >= _resource->frames.size())
     {
         return;
     }
 
     _frameIndex = index;
     _frame = _resource->frames[_frameIndex];
     SyncSizeWithSource();
 }
 
 /**
  * 
  * Hitbox visual
  * 
  */
 
 void SpriteV2::SetDrawHitboxes(bool value)
 {
     _drawHitboxes = value;
 }
 
 bool SpriteV2::GetDrawHitboxes()
 {
     return _drawHitboxes;
 }
 
 void SpriteV2::SetCanDrawHiboxes(bool canDraw)
 {
     _canDrawHitboxes = canDraw;
 }
 
 /**
  * 
  * Hitbox
  * 
  */
 
 Rectangle SpriteV2::GetRect() const
 {
     return GetWorldRect();
 }
 
 void SpriteV2::SetRectSize(Vector2 newSize)
 {
     _rect.width = newSize.x;
     _rect.height = newSize.y;
 }
 
 bool SpriteV2::IsCollide() const
 {
     return _collision;
 }
 
 void SpriteV2::SetCollide(bool isCollide)
 {
     _collision = isCollide;
 }
 
 /**
  *  
  * Core
  * 
  */
 
  void SpriteV2::Draw()
  {
      if (!HasResource())
          return;
  
      Rectangle dest = {_position.x, _position.y, _size.x, _size.y};
      Vector2 origin = {_size.x * 0.5f, _size.y * 0.5f};

      bool useBrightness = _shaderLoaded && (_brightness != 1.0f);

      if (useBrightness)
     {
        BeginShaderMode(_brightnessShader);
        SetShaderValue(_brightnessShader, _brightnessLoc, &_brightness, SHADER_UNIFORM_FLOAT);
     }

      DrawTexturePro(_resource->texture, GetSource(), dest, origin, _rotation, Fade(WHITE, _alpha));
     
      if (useBrightness)
        EndShaderMode();

      if (_drawHitboxes && _canDrawHitboxes)
      {
          Vector2 rectOrigin = {_rect.width * 0.5f, _rect.height * 0.5f};
  
          DrawRectanglePro(
              {_position.x, _position.y, _rect.width, _rect.height},
              rectOrigin,
              _rotation,
              Fade(WHITE, 0.5f)
          );
      }
  }
 
 /**
  * 
  * Misc
  * 
  */
 
 bool SpriteV2::HasResource() const
 {
     return _resource && _resource->texture.id != 0;
 }
 
 bool SpriteV2::HasAtlas() const
 {
     return HasResource() && !_resource->frames.empty();
 }
 
 Rectangle SpriteV2::GetSource() const
 {
     return _frame;
 }
 
 void SpriteV2::SyncSizeWithSource()
 {
     Rectangle source = GetSource();
     _size = {source.width, source.height};
     _rect.width = _size.x;
     _rect.height = _size.y;
 }
 
 Rectangle SpriteV2::GetWorldRect() const
 {
     return GetWorldRect(_position);
 }
 
 Rectangle SpriteV2::GetWorldRect(Vector2 position) const
 {
     return {
         position.x - _rect.width * 0.5f,
         position.y - _rect.height * 0.5f,
         _rect.width,
         _rect.height
     };
 }
 