#pragma once

#include <vector>
#include <memory>

#include "mapItem.h"

class MapItemManager {
public:
    static void SpawnItem(ItemID id);
    static void SpawnItem(ItemID id, MapLocation loc);

    static void Init(TextureResource* itemIconsPack);
    static void Draw();
    static void Update(float dt, const SpriteV2& playerSprite);

private:
    static std::vector<std::unique_ptr<MapItem>> _items;
    static TextureResource* _itemIconsPack;
};