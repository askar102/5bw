#pragma once

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

private:
    SpriteV2 _popup;
    SpriteV2 _emotion;

    bool _visible = false;
    const SpriteV2* _anchor;
 };