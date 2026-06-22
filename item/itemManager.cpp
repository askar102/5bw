#include "itemManager.h"

std::unordered_map<ItemID, ItemInfo> ItemManager::_items;

void ItemManager::Init() {
    _items[ItemID::Chalk] = {
        "Pizda",
        "huy"
    };
}

ItemInfo ItemManager::GetInfo(ItemID itemId) {
    auto item = _items.find(itemId);
    if (item != _items.end()) {
        return item->second;
    }
}