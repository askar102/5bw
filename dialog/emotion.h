#pragma once

// Пофиксить что когда стаившь BIG, то сразу две появляются
// ПОСТАВИТЬ ровно над персонажем
// Сделать чтобы эмодзи показывалось а не только поп ап
// https://youtu.be/wkRwyj1xbxI?t=536
// Сделать чтобы не было BIG/ SMALL, а вначале увеличился SMALL, потом появился с увелеченим BIG
#include <cstdint>
#include <vector>

#include "../core/resourceManager.h"

#include "../entities/spriteV2.h"

enum class PopupSize {
    SMALL, BIG
};

// добавлено Клодом, индексы сверены с askar102 2026-07-21 (заменяет прошлую версию, которая была неточной)
enum class EmotionType : int32_t {
    Exclaim    = 2,  // анимация 2, 3, 4
    Question   = 5,
    Love       = 6,
    Drop       = 7,
    Irritation = 8,
    LampOff    = 9,
    LampOn     = 10,
    Confusion  = 11, // анимация 11, 12, 13, loop
    Sleep      = 14
    // 15 - пустой слот 48x48 в emotionPack.png, зарезервирован под кастомные эмодзи, см. Emotion::ShowCustom
};

class Emotion {
public:
    void Init(const SpriteV2* anchor);
    void Show(EmotionType type, PopupSize size, float duration);

    // добавлено Клодом: вставить в попап произвольную картинку вместо кадра из emotionPack.png,
    // она подгоняется под тот же размер, что обычная иконка эмоции (48x48)
    void ShowCustom(TextureResource* customTexture, PopupSize size, float duration);

    void Update(float dt);
    void Draw();

    bool IsVisible() const { return _visible; }
    void Hide();

private:
    SpriteV2 _popup;
    SpriteV2 _emotion;

    TextureResource* _defaultEmotionTexture = nullptr; // добавлено Клодом: чтобы вернуться к атласу после ShowCustom

    bool _visible = false;
    const SpriteV2* _anchor = nullptr;
    float _animationTimer = 0.0f;
    float _animationDuration = 3.0f;
 };