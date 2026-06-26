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

enum class EmotionType : int32_t {
    QUESTION = 5,
    LOVE = 6,
    SAD = 8,
    MAD = 10,
    NO_IDEA = 11,
    IDEA = 12,
    BROKEN = 15 // TODO: add animation here (15, 16, 17)
};

class Emotion {
public:
    void Init(const SpriteV2* anchor);
    void Show(EmotionType type, PopupSize size, float duration);

    void Update(float dt);
    void Draw();

    bool IsVisible() const { return _visible; }
    void Hide();

private:
    SpriteV2 _popup;
    SpriteV2 _emotion;

    bool _visible = false;
    const SpriteV2* _anchor = nullptr;
    float _animationTimer = 0.0f;
    float _animationDuration = 3.0f;
 };