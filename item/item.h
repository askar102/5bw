#pragma once

#include <string>
#include <map>

#include "itemId.h"

enum class ItemType {
    Default = 0,
    Usable = 1
};

struct ItemInfo {
    std::string title;
    std::string description;
    ItemType type = ItemType::Default;
};

struct Item {
    ItemID id;
    ItemInfo info;

    bool operator<(const Item& other) const {
        return std::tie(id, info.title, info.description) < std::tie(other.id, other.info.title, other.info.description);
    }
}; 

