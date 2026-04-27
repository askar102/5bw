#pragma once

#include "vfx.h"

class CardVfx : public Vfx {
public:
    CardVfx(Vector2 position, float lifetime, float rotation, Texture2D* texture);

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;
    bool IsFinished() const override;
};
    
