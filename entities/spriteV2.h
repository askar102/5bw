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

 #include "../raylib/raylib.h"
 #include "../core/resourceManager.h"
 
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
     static Shader _brightnessShader;
     static int _brightnessLoc;
     static bool _shaderLoaded;  
 
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
     void SyncSizeWithSource();

     // frame timer
    int _timerReturnFrame = 0;
    float _frameTimer = 0.0f;
    float _frameTimerDuration = 0.0f;
    bool _frameTimerActive = false;
    std::function<void()> _frameTimerCallback;
 
 public:
     // resources
     void SetResource(TextureResource* newResource);
 
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


     // core
     void Draw();
     void Update(float dt);
 };
 