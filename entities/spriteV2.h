/**
 * @file sprite.h
 * @author askar102
 * @brief Sprite type
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

 #pragma once

 #include <functional>
 #include <math.h>

 #include "../raylib/raylib.h"
 #include "../core/resourceManager.h"

 #include "../misc/floatingText.h"
 
 class SpriteV2 {
 private:
     // resources
     TextureResource* _resource = nullptr;
 
     // visual
     Vector2 _position{0.0f, 0.0f};
     Vector2 _size{0.0f, 0.0f};
     float _rotation = 0.0f;

     // effects
     float _alpha = 1.0f;
     float _brightness = 1.0f;

     bool _alphaFlashing = false;
     float _alphaFlashTimer = 0.0f;
     static constexpr float ALPHA_FLASH_PERIOD = 0.1f;

     static Shader _brightnessShader;
     static int _brightnessLoc;
     static bool _shaderLoaded;  

     bool _shaking = false;
    float _shakeTimer = 0.0f;
    float _shakeDuration = 0.0f;
    float _shakeIntensity = 4.0f;
    Vector2 _shakeOffset{0.0f, 0.0f};

    // brightness flashing
    bool _brightnessFlashing = false;
    float _brightnessFlashTimer = 0.0f;
    float _brightnessFlashDuration = 0.0f;
    std::function<void()> _brightnessFlashOnDone;
    static constexpr float BRIGHTNESS_FLASH_PERIOD = 0.15f;

    // brightening up
    bool _brighteningUp = false;
    float _brightenTimer = 0.0f;
    float _brightenDuration = 0.0f;
    std::function<void()> _brightenOnDone;
    static constexpr float BRIGHTNESS_MAX = 2.5f;
    
    // floating text
    FloatingText _text;

     // atlas
     Rectangle _frame{0.0f, 0.0f, 0.0f, 0.0f};
     size_t _frameIndex = 0;
 
     // hitbox visual
     static bool _drawHitboxes;
     bool _canDrawHitboxes = true;
 
     // hitbox
     Rectangle _rect{_position.x, _position.y, _size.x, _size.y};
     bool _collision = true;
 
     bool HasResource() const;
     bool HasAtlas() const;
     Rectangle GetSource() const;
     

     // frame timer
    int _timerReturnFrame = 0;
    float _frameTimer = 0.0f;
    float _frameTimerDuration = 0.0f;
    bool _frameTimerActive = false;
    std::function<void()> _frameTimerCallback;
 
 public:
     // resources
     void SetResource(TextureResource* newResource);
    
     Rectangle GetSourceRect() const { return _frame; }
     size_t GetSourceRectIndex() const { return _frameIndex; }

     void SyncSizeWithSource();

     // visual
     Vector2 GetPosition() const;
     void SetPosition(Vector2 newPosition);
 
     Vector2 GetSize() const;
     void SetSize(Vector2 newSize);
 
     float GetRotation() const;
     void SetRotation(float newRotation);
 
     float GetAlpha() const;
     void SetAlpha(float newAlpha);

     float GetBrightness() const;
     void SetBrightness(float newBrightness);
     static void LoadBrightnessShader();
     static void UnloadBrightnessShader();

     void SetAlphaFlashing(bool flashing);
     void UpdateAlphaFlashing(float dt);

     void SetShaking(bool shaking, float duration = 0.3f, float intensity = 4.0f);
    void UpdateShaking(float dt);
    Vector2 GetShakeOffset() const { return _shakeOffset; }

    void SetBrightnessFlashing(bool flag, float duration = 1.0f, std::function<void()> onDone = nullptr);
    void UpdateBrightnessFlashing(float dt);

    void SetBrighteningUp(float duration, std::function<void()> onDone = nullptr);
    void UpdateBrighteningUp(float dt);
 
     // atlas
     void SetFrame(size_t index);
     void SetFrameTime(size_t frame, float duration, std::function<void()> onDone = nullptr);
     void SetFrameTime(size_t frame, size_t returnFrame, float duration, std::function<void()> onDone = nullptr);
 
     // hitbox visual
     static void SetDrawHitboxes(bool value);
     static bool GetDrawHitboxes();
 
     void SetCanDrawHiboxes(bool canDraw);
 
     // hitbox
     Rectangle GetRect() const;
     Rectangle GetWorldRect() const;
     Rectangle GetWorldRect(Vector2 position) const;
     void SetRectSize(Vector2 newSize);
 
     bool IsCollide() const;
     void SetCollide(bool isCollide);
    
    // misc
    bool IsSpriteOnScreen();
    FloatingText& GetText() { return _text; }

     // core
     void Draw();
     void Update(float dt);
 };
 