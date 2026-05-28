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

float SpriteV2::GetBrightness() const {
    return _brightness; 
}
 
void SpriteV2::SetBrightness(float newBrightness) {
    _brightness = newBrightness; 
}

void SpriteV2::SetFlashing(bool flashing)
{
    _flashing = flashing;
    if (!flashing)
    {
        _alpha = 1.0f;
        _flashTimer = 0.0f;
    }
}


void SpriteV2::UpdateFlashing(float dt)
{
    if (!_flashing) return;

    _flashTimer += dt;

    // пилообразная волна 0..FLASH_PERIOD -> альфа туда-обратно
    float t = fmod(_flashTimer, FLASH_PERIOD) / FLASH_PERIOD; // 0..1
    // синус даёт плавное мигание; можно заменить на step если надо резкое
    _alpha = 0.2f + 0.8f * (0.5f + 0.5f * sinf(t * 2.0f * PI));
}

void SpriteV2::SetShaking(bool shaking, float duration, float intensity)
{
    _shaking = shaking;
    _shakeDuration = duration;
    _shakeTimer = shaking ? duration : 0.0f;
    _shakeIntensity = intensity;
    _shakeOffset = {0.0f, 0.0f};
}

void SpriteV2::UpdateShaking(float dt)
{
    if (!_shaking) return;

    _shakeTimer -= dt;

    if (_shakeTimer <= 0.0f)
    {
        _shaking = false;
        _shakeOffset = {0.0f, 0.0f};
        return;
    }

    float t = _shakeTimer / _shakeDuration; // 1 -> 0, fade out intensity
    float mag = _shakeIntensity * t;
    _shakeOffset = {
        (float)(GetRandomValue(-100, 100) / 100.0f) * mag,
        (float)(GetRandomValue(-100, 100) / 100.0f) * mag
    };
}
 
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

 void SpriteV2::SetFrameTime(size_t frame, float duration, std::function<void()> onDone)
{
    SetFrame(frame);
    _frameTimerDuration = duration;
    _frameTimer = 0.0f;
    _frameTimerActive = true;
    _timerReturnFrame = -1; // нет возврата
    _frameTimerCallback = std::move(onDone);
}

void SpriteV2::SetFrameTime(size_t frame, size_t returnFrame, float duration, std::function<void()> onDone)
{
    SetFrame(frame);
    _frameTimerDuration = duration;
    _frameTimer = 0.0f;
    _frameTimerActive = true;
    _timerReturnFrame = static_cast<int>(returnFrame);
    _frameTimerCallback = std::move(onDone);
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
 * Misc 
 *
 */

 bool SpriteV2::IsSpriteOnScreen()
 {
    Rectangle rect = this->GetRect();

    return rect.x >= 0 &&
           rect.y >= 0 &&
           rect.x + rect.width <= GetScreenWidth() &&
           rect.y + rect.height <= GetScreenHeight();
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

      Vector2 drawPos = {
        _position.x + _shakeOffset.x,
        _position.y + _shakeOffset.y
    };
  
      Rectangle dest = {drawPos.x, drawPos.y, _size.x, _size.y};
      Vector2 origin = {_size.x * 0.5f, _size.y * 0.5f};

      bool useBrightness = _shaderLoaded && (_brightness != 1.0f);

    if (useBrightness)
     {
        BeginShaderMode(_brightnessShader);
        SetShaderValue(_brightnessShader, _brightnessLoc, &_brightness, SHADER_UNIFORM_FLOAT);
     }

      DrawTexturePro(_resource->texture, GetSource(), dest, origin, _rotation, Fade(WHITE, _alpha));
     
      if (useBrightness)
      {
        EndShaderMode();
      }
        

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

void SpriteV2::Update(float dt)
{
    UpdateFlashing(dt); 
    UpdateShaking(dt);

    if (!_frameTimerActive) return;

    _frameTimer += dt;
    if (_frameTimer < _frameTimerDuration) return;

    _frameTimerActive = false;

    if (_timerReturnFrame >= 0)
        SetFrame(static_cast<size_t>(_timerReturnFrame));

    if (_frameTimerCallback)
    {
        _frameTimerCallback();
        _frameTimerCallback = nullptr;
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
 