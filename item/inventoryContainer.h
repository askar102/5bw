#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <map>
#include <utility>

#include "item.h"
#include "itemManager.h"

class InventoryContainer {
public:
    void Add(ItemID newItemId, uint32_t count);
private:
    std::map<ItemID, std::pair<std::unique_ptr<Item>, uint32_t>> _items;
};