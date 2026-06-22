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