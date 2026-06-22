#pragma once

#include "inventoryContainer.h"
#include "itemManager.h"

class Inventory {
public:    
    static void Init(); // Here we going to use itemManager::Init(), instead use it in mapState
    static void Add(ItemID newItemId, uint32_t count = 1);
    static InventoryContainer& GetContainer() { return _container; }

    // misc (maybe for fast testing)
    static std::vector<std::string> GetAsString(); // array of titles
private:
    static InventoryContainer _container;
};