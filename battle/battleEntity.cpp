#include "battleEntity.h"

void BattleEntity::Draw() 
{
    sprite.Draw();
    
    Vector2 pos = sprite.getPosition();
    DrawText(TextFormat("Selected: %d", selected), pos.x, (pos.y - 30), 20, WHITE);
}

void BattleEntity::DrawAbilities() 
{
    Vector2 pos = sprite.getPosition();
    Vector2 newPos{pos.x + 50, pos.y};

    for (const auto& ability : abilities) 
    {
        if (!ability) {
            continue;
        }

        // только текст
        DrawText(
            ability->name.c_str(),
            newPos.x,
            newPos.y,
            20,
            WHITE
        );

        newPos.y += 40;
    }
}

void BattleEntity::UpdateAbilities()
{
}