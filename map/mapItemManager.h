#include <vector>
#include <memory>

#include "mapItem.h"

class MapItemManager {
public:
    static void SpawnItem(ItemID id);
    static void SpawnItem(ItemID id, MapLocation loc);

    static void Init(TextureResource* itemIconsPack);
    static void Draw();
    static void Update(float dt);
private:
    std::vector<std::unique_ptr<MapItem>> _items;
    TextureResource* _itemIconsPack;
};