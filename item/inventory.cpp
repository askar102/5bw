#include "inventory.h"

InventoryContainer Inventory::_container; 

void Inventory::Init() {
    ItemManager::Init();
}

void Inventory::Add(ItemID newItemId, uint32_t count) {
    _container.Add(newItemId, count);
}

std::vector<std::string> Inventory::GetAsString() {
    std::vector<std::string> strs;
    
    for (auto& [id, item] : _container.GetItems() ) {
        strs.push_back(item.first->info.title);
    } 
    
    return strs;
}

void Inventory::Remove(ItemID existItemId, uint32_t count) {
    _container.Remove(existItemId, count);
}