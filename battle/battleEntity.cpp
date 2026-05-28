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
            trail.Init(20, 1.0f, 0.01f);
        }
    }

void BattleEntity::Draw()
{
    sprite.Draw();
    trail.Draw(this->getSprite());
    // dont move this function!
    RefreshActionText();
    actionText.Draw();

    effectLabel.Draw(sprite.GetPosition(), sprite.GetSize());
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
    if (amount < 0) return;

    int reduced = amount - GetWeaknessEffect();
    if (reduced < 0) reduced = 0;

    this->hp = std::max(hp - reduced, 0);
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
    sprite.Update(dt);

    UpdateEnemyWhirl();

    // Movement actions
    UpdateMove(dt);
    UpdateTurn(dt);

    // logic effects
    UpdateWeaknessEffect(dt);
    effectLabel.Update(dt); 

    // Abilities
    UpdateAbilities();

    // visual effects
    trail.Update(dt, this->getSprite());
}

void BattleEntity::MoveTo(float targetX, float speed, std::function<void()> onStop)
{
    _moveTargetX = targetX;
    _moveSpeed = speed;
    _moving = true;
    _onStop = onStop;
}

void BattleEntity::MoveTo(BattleEntity& target, float speed, std::function<void()> onStop)
{
    _moveTargetX = target.getSprite().GetPosition().x;
    _moveSpeed = speed;
    _moving = true;
    _onStop = onStop;
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
        sprite.SetPosition(pos);
        if (_onStop)
        {
            _onStop();
        }
        return;
    }

    sprite.SetPosition(pos);
}

void BattleEntity::SetOnTouch(std::function<void(BattleEntity&)> onTouch)
{
    _onTouch = std::move(onTouch);
}

void BattleEntity::ClearOnTouch()
{
    _onTouch = nullptr;
    _touchedEntities.clear();
}

void BattleEntity::ResetTouchTracking()
{
    _touchedEntities.clear();
}

void BattleEntity::CheckTouch(BattleEntity* const* others, size_t count)
{
    if (!_onTouch)
        return;

    const Rectangle myRect = sprite.GetRect();

    for (size_t i = 0; i < count; ++i)
    {
        BattleEntity* other = others[i];
        if (!other || other == this || !other->Alive())
            continue;

        if (_touchedEntities.contains(other))
            continue;

        if (!CheckCollisionRecs(myRect, other->getSprite().GetRect()))
            continue;

        _touchedEntities.insert(other);
        _onTouch(*other);
    }
}

void BattleEntity::TurnDegrees(float degrees, float speed, int times, std::function<void()> onDone)
{
    if (times <= 0 || speed <= 0.0f) return;

    _turning           = true;
    _turnDegreesPerPass = degrees;
    _turnSpeed         = speed;
    _turnTimesLeft     = times;
    _onTurnDone        = onDone;

    //cтартуем первый проход
    _turnDelta  = degrees;
    _turnTarget = sprite.GetRotation() + degrees;
}

void BattleEntity::UpdateTurn(float dt)
{
    if (!_turning) return;

    float step = _turnSpeed * dt;
    float sign = (_turnDelta >= 0.0f) ? 1.0f : -1.0f;
    float moved = sign * std::min(step, std::abs(_turnDelta));

    sprite.SetRotation(sprite.GetRotation() + moved);
    _turnDelta -= moved;

    if (std::abs(_turnDelta) < 0.001f)
    {
        sprite.SetRotation(_turnTarget);
        _turnTimesLeft--;

        if (_turnTimesLeft > 0)
        {
            _turnDelta  = _turnDegreesPerPass;
            _turnTarget = sprite.GetRotation() + _turnDegreesPerPass;
        }
        else
        {
            _turning = false;
            if (_onTurnDone)
                _onTurnDone();
        }
    }
}

/**
 * LOGIC EFFECTS
 * 
 */

void BattleEntity::SetWeaknessEffect(int amount, float duration, std::function<void()> onDone)
{
    _weaknessAmount   = amount;
    _weaknessDuration = duration;
    _weaknessActive   = true;
    _weaknessOnDone = std::move(onDone);
    // visual
    effectLabel.Show("weaknessEffect", 2.0f);
}


int BattleEntity::GetWeaknessEffect() 
{
    return _weaknessActive ? _weaknessAmount : 0;
}

void BattleEntity::UpdateWeaknessEffect(float dt)
{
    if (!_weaknessActive) return;

    _weaknessDuration -= dt;

    if (_weaknessDuration <= 0.0f)
    {
        _weaknessDuration = 0.0f;
        _weaknessAmount   = 0;
        _weaknessActive   = false;

        if (_weaknessOnDone)
        {
            _weaknessOnDone();
            _weaknessOnDone = nullptr;
        }
    }
}