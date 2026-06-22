#pragma once

#include "../map/mapItem.h"

struct ItemInfo {
    std::string title;
    std::string description;
};

struct Item {
    ItemID id;
    ItemInfo info;

    bool operator<(const Item& other) const {
        return std::tie(id, info.title, info.description) < std::tie(other.id, other.info.title, other.info.description);
    }
}; 

