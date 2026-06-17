#include "../entities/spriteV2.h"

#include "mapLocation.h"

enum class ItemID {
    Chalk = 0,
    Kvass = 1
};

class MapItem {
public:
    MapItem(ItemID id, MapLocation loc, TextureResource& iconsTx)
        : _id(id), _loc(loc)
    {
        _icon.SetResource(&iconsTx);
        _icon.SetFrame((size_t)_id);
    } 

    const ItemID& GetId() { return _id; }
    SpriteV2& GetIcon() { return _icon; }

    void CheckCollision(Rectangle& playerRect);
private:
    ItemID _id;
    SpriteV2 _icon;

    MapLocation _loc;
};