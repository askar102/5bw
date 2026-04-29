#include "battleEntity.h"

void BattleEntity::Draw() 
{
    UpdateEnemyWhirl();
    sprite.Draw();
    RefreshActionText();
    actionText.Draw();
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
            ability->getName().c_str(),
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

void BattleEntity::RefreshActionText()
{
    Vector2 pos = sprite.getPosition();
    actionText.SetAnchor(pos);

    actionText.SetLine(0, TextFormat("HP: %d", hp));

    if (canSelected)
    {
        actionText.SetLine(1, TextFormat("Selected: %d", selected));
    }
    else
    {
        actionText.SetLine(1, "Cant be selected");
    }
}

/**
 * BATTLE ACTIONS
 * 
 */

 void BattleEntity::Heal(int amount)
 {
    this->hp = std::min(hp + amount, maxHp);
 }


 /**
  * @brief снять хп у юнита
  * @details вначале минусуем хп, потом  
  * чекаем, если это противник + анимация еще не активна
  * то двигаем его на -15.0f назад, потом записываем время, когда анимация пропадет
  * 
  *
  * @param amount 
  */
 void BattleEntity::Damage(int amount)
 {
    if (amount < 0) 
        return;

    this->hp = std::max(hp - amount, 0);

    if (isEnemy && !_enemyWhirlActive) 
    {
        Vector2 position = sprite.getPosition();
        position.x += ENEMY_WHIRL_PUSH_X;
        sprite.setPosition(position);
        _enemyWhirlActive = true;
    }

    _enemyWhirlResetAt = GetTime() + ENEMY_WHIRL_DURATION;
 }


/**
 * @brief чекаем не завершилась ли анимация попадания
 * 
 */
void BattleEntity::UpdateEnemyWhirl()
{
    if (!_enemyWhirlActive || GetTime() < _enemyWhirlResetAt) 
    {
        return;
    }

    Vector2 position = sprite.getPosition();
    position.x -= ENEMY_WHIRL_PUSH_X;
    sprite.setPosition(position);

    _enemyWhirlActive = false;
}

