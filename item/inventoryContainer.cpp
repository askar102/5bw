#include "inventoryContainer.h"

void InventoryContainer::Add(ItemID newItemId, uint32_t count) {
    auto it = _items.find(newItemId);

    if (it != _items.end()) 
    {
        it->second.second += count;
    } 
    else 
    {
        auto itemPtr = std::make_unique<Item>(Item{
            newItemId,
            ItemManager::GetInfo(newItemId)
        });

        _items[newItemId] = std::make_pair(std::move(itemPtr), count);
    }
}

std::vector<std::string> InventoryContainer::GetAsString() {
    std::vector<std::string> strs;

    for (auto& [id, item] : _items) {
        strs.push_back(item.first->info.title);
    } 

    return strs;
}