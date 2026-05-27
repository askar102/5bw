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

BattleEntity::BattleEntity(std::string _name, int _maxHp, bool _isEnemy, bool _canSelected, std::vector<Ability> _abilities, FacingDirection _facingDirection)
    : name(_name), maxHp(_maxHp), isEnemy(_isEnemy), canSelected(_canSelected), facing(_facingDirection) {
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
    position.x -= _whirlPushApplied;
    sprite.SetPosition(position);

    _enemyWhirlActive = false;
    _whirlPushApplied = 0.0f;
}

void BattleEntity::EnemyHitAnimation()
{
    if (!_enemyWhirlActive)
    {
        _whirlPushApplied = (facing == FacingDirection::Left)
            ? ENEMY_WHIRL_PUSH_X
            : -ENEMY_WHIRL_PUSH_X;

        Vector2 position = sprite.GetPosition();
        position.x += _whirlPushApplied;
        sprite.SetPosition(position);
        _enemyWhirlActive = true;
    }

    _enemyWhirlResetAt = GetTime() + ENEMY_WHIRL_DURATION;
}


void BattleEntity::Update(float dt)
{
    UpdateEnemyWhirl();
    
    UpdateMove(dt);

    UpdateAbilities();
}

void BattleEntity::MoveTo(float targetX, float speed)
{
    _moveTargetX = targetX;
    _moveSpeed = speed;
    _moving = true;
}

void BattleEntity::UpdateMove(float dt)
{
    if (!_moving) return;

    Vector2 pos = sprite.GetPosition();
    float dir = (_moveTargetX > pos.x) ? 1.0f : -1.0f;

    pos.x += dir * _moveSpeed * dt;

    if ((dir > 0 && pos.x >= _moveTargetX) ||
        (dir < 0 && pos.x <= _moveTargetX))
    {
        pos.x = _moveTargetX;
        _moving = false;
    }

    sprite.SetPosition(pos);
}

