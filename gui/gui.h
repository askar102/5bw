#pragma once

#include <string>
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

class Gui {
public:
    void SetResource(TextureResource* resource);
    void SetPosition(Vector2 position);
    void SetVisible(bool visible);
    virtual void Draw();
    virtual void Update();

    SpriteV2& GetSprite();

protected:
    SpriteV2 _sprite;
    bool _visible = true;
};