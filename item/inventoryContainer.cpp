#include "inventoryContainer.h"
#include <iterator>

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

void InventoryContainer::Remove(ItemID existItemId, uint32_t count) {
    auto itemIt = _items.find(existItemId);
    if (itemIt != _items.end()) {
        uint32_t& currentCount = itemIt->second.second;

        if (count >= currentCount) {
            _items.erase(itemIt);
        } else {
            currentCount -= count;
        }
    }
}