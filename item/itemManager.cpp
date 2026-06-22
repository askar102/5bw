#include "itemManager.h"
#include "itemId.h"

std::unordered_map<ItemID, ItemInfo> ItemManager::_items;

void ItemManager::Init() {
    _items[ItemID::Chalk] = {
        "Pizda",
        "huy"
    };

    _items[ItemID::Kvass] = {
        "Kvass",
        "Zakamskie kvass. Taste is not shit"
    };
}

ItemInfo ItemManager::GetInfo(ItemID itemId) {
    auto item = _items.find(itemId);
    if (item != _items.end()) {
        return item->second;
    } else return {"idk_title", "idk_desc"};
}