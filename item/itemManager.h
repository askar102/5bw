#pragma once

#include <unordered_map>

#include "item.h"

class ItemManager {
public:
    static void Init();
    static ItemInfo GetInfo(ItemID itemId);
private:
    static std::unordered_map<ItemID, ItemInfo> _items;
};