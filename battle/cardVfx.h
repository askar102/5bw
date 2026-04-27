#pragma once

#include "vfx.h"
#include "../entities/sprite.h"

class CardVfx : public Vfx {
public:
    CardVfx(Vector2 position, float lifetime, Texture2D* texture);

    void Update(float dt) override;
    void Draw() override;
    bool IsFinished() const override;

private:
    Sprite _sprite;
};
    