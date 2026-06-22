#include "mapItemManager.h"

std::vector<std::unique_ptr<MapItem>> MapItemManager::_items;
TextureResource* MapItemManager::_itemIconsPack = nullptr;

void MapItemManager::Init(TextureResource* itemIconsPack)
{
    _itemIconsPack = itemIconsPack;
}

void MapItemManager::SpawnItem(ItemID id, MapLocation loc)
{
    if (!_itemIconsPack) return;

    _items.push_back(std::make_unique<MapItem>(id, loc, *_itemIconsPack));
}

void MapItemManager::SpawnItem(ItemID id)
{
    SpawnItem(id, MapLocation{0, 0, 0, 0});
}

void MapItemManager::Update(float dt, const SpriteV2& playerSprite)
{
    for (auto& item : _items)
    {
        item->Update(dt, playerSprite);
    }
}

void MapItemManager::Draw()
{
    for (auto& item : _items)
    {
        item->Draw();
    }
}