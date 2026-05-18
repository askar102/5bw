/**
 * @file battleEntity.cpp
 * @author askar102
 * @brief Battle entity type
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "battleEntity.h"

BattleEntity::BattleEntity(std::string _name, int _maxHp, bool _isEnemy, bool _canSelected, std::vector<Ability> _abilities)
    : name(_name), maxHp(_maxHp), isEnemy(_isEnemy), canSelected(_canSelected) {
        for (Ability ab : _abilities)
        {
            abilities.push_back(std::make_unique<Ability>(ab));
        }
    }

void BattleEntity::Draw()
{
    sprite.Draw();
    // dont move this function!
    RefreshActionText();
    actionText.Draw();
}

void BattleEntity::DrawAbilities() 
{
    Vector2 pos = sprite.GetPosition();
    Vector2 newPos{pos.x + 50, pos.y};

    for (const auto& ability : abilities) 
    {
        if (!ability) {
            continue;
        }

        // только текст
        DrawText(
            ability->GetName().c_str(),
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
    Vector2 pos = sprite.GetPosition();
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
  * @brief снять хп у юнита & анимация попадания
  * 
  * @param amount 
  */
 void BattleEntity::Damage(int amount)
 {
    if (amount < 0) 
        return;

    this->hp = std::max(hp - amount, 0);
 }


/**
 * @brief чекаем не завершилась ли анимация попадания, и есть ли она вообще
 * 
 */
void BattleEntity::UpdateEnemyWhirl()
{
    if (!_enemyWhirlActive || GetTime() < _enemyWhirlResetAt) 
    {
        return;
    }

    Vector2 position = sprite.GetPosition();
    position.x -= ENEMY_WHIRL_PUSH_X;
    sprite.SetPosition(position);

    _enemyWhirlActive = false;
}

/**
 * если это противник + анимация еще не активна
  * то двигаем его на -15.0f назад, потом записываем время, когда анимация пропадет
 * 
 */
void BattleEntity::EnemyHitAnimation()
{
    if (isEnemy && !_enemyWhirlActive) 
    {
        Vector2 position = sprite.GetPosition();
        position.x += ENEMY_WHIRL_PUSH_X;
        sprite.SetPosition(position);
        _enemyWhirlActive = true;
    }

    _enemyWhirlResetAt = GetTime() + ENEMY_WHIRL_DURATION;
}


void BattleEntity::Update(float dt)
{
    UpdateEnemyWhirl();
    
    UpdateSelection();
    UpdateAbilities();
}

void BattleEntity::UpdateSelection()
{
    if (!canSelected)
        return;

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, sprite.GetRect()))
        {
            selected = !selected;
        }
    }
}