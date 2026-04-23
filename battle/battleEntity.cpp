#include "battleEntity.h"

void BattleEntity::Draw() 
{
    sprite.Draw();
    
    InitText();
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

/**
 * BATTLE ACTIONS
 * 
 */

 void BattleEntity::Heal(unsigned int amount)
 {
    this->hp = std::min<unsigned int>(hp + amount, maxHp);
 }

 void BattleEntity::Damage(unsigned int amount)
 {
    this->hp = std::max<unsigned int>(hp - amount, 0);
 }

/**
 * MISC
 * 
 */

void BattleEntity::InitText()
{
    Vector2 pos = sprite.getPosition();

    DrawText(TextFormat("HP: %d", hp), pos.x, (pos.y - 60), 20, WHITE);

    if (canSelected) 
    {
        DrawText(TextFormat("Selected: %d", selected), pos.x, (pos.y - 30), 20, WHITE);
    }
    else 
    {
        DrawText("Cant be selected", (pos.x - 20), (pos.y - 30), 20, WHITE);
    }
}