#pragma once

#include "../entities/spriteV2.h"

#include "mapLocation.h"

enum class ItemID {
    Chalk = 0,
    Kvass = 1
};

class MapItem {
public:
    MapItem(ItemID id, MapLocation loc, TextureResource& iconsTx)
        : _id(id), _loc(loc)
    {
        _icon.SetResource(&iconsTx);
        _icon.SetFrame((size_t)_id);
        MapLocator::PlaceSprite(_icon, loc);
    } 

    const ItemID& GetId() { return _id; }
    SpriteV2& GetIcon() { return _icon; }

    void CheckCollision(const SpriteV2& playerSprite);
    void Update(float dt, const SpriteV2& playerSprite);
    void Draw();
private:
    ItemID _id;
    SpriteV2 _icon;

    MapLocation _loc;

    const SpriteV2* _anchor = nullptr;
    float _bringAnimationTimer = 0.0f;
    float _bringAnimationDuration = 3.0f;

    bool _destoyed = false;
};