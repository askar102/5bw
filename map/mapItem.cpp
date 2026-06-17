#include "mapItem.h"

void MapItem::CheckCollision(const Rectangle& playerRect) {
    if (CheckCollisionRecs(_icon.GetRect(), playerRect)) {
        _icon.SetAlpha(0.0f);
    }
}