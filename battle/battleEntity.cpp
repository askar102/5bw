#include "battleEntity.h"

void BattleEntity::Draw() {
    sprite.Draw();
    
    Vector2 pos = sprite.getPosition();
    DrawText(TextFormat("Selected: %d", selected), pos.x, (pos.y - 30), 20, WHITE);
}