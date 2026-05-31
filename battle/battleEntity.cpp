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
#include <string>

BattleEntity::BattleEntity(std::string _name, int _maxHp, bool _isEnemy, bool _canSelected, std::vector<Ability> _abilities, FacingDirection _facingDirection)
    : name(_name), maxHp(_maxHp), isEnemy(_isEnemy), canSelected(_canSelected), facing(_facingDirection) {
        for (Ability ab : _abilities)
        {
            abilities.push_back(std::make_unique<Ability>(ab));
            trail.Init(20, 1.0f, 0.01f);
        }
    }

BattleEntity::BattleEntity() {}

void BattleEntity::Draw()
{
    sprite.Draw();
    trail.Draw(this->getSprite());
    // dont move this function!
    RefreshActionText();
    actionText.Draw();

    effectLabel.Draw(sprite.GetPosition(), sprite.GetSize());
    effectIcons.Draw(getSprite());

    minigame.Draw(getSprite());
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
    if (immortal) return; 

    if (amount <= 0) return;

    this->hp = std::min(hp + amount, maxHp);
    effectLabel.Show("healEffect", 1.0f);

    Rectangle rect = getSprite().GetWorldRect();
    Vector2 topLeft = {rect.x, rect.y};

    getSprite().GetText().Show("+" + std::to_string(amount), {topLeft.x + 40.0f, topLeft.y}, 1.0f, GREEN);
 }


 /**
  * @brief снять хп у юнита & анимация попадания
  * 
  * @param amount 
  */
 void BattleEntity::Damage(int amount, BattleEntity* source)
 {
    if (immortal) return; 

    int finalAmount = amount;

    if (source && source->GetWeaknessEffect() > 0)
        finalAmount -= source->GetWeaknessEffect();

    if (finalAmount < 0) finalAmount = 0;
    if (finalAmount == 0 || hp <= 0) return;

    this->hp = std::max(hp - finalAmount, 0);

    Rectangle rect = getSprite().GetWorldRect();
    Vector2 topLeft = {rect.x, rect.y};

    getSprite().GetText().Show("-" + std::to_string(finalAmount), {topLeft.x + 40.0f, topLeft.y}, 1.0f, RED);
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
    if (immortal) return;

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
    UpdateScreamEffect(dt);
    UpdateStunEffect(dt);
    UpdateTimestopEffect(dt);

    effectLabel.Update(dt); 
    effectIcons.Update(dt);

    minigame.Update(dt);

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
    if (_movingToTarget)
    {
        if (!_moveTarget || !_moveTarget->Alive())
        {
            _movingToTarget = false;
            _moveTarget = nullptr;
            if (_onStop)
            {
                auto cb = std::move(_onStop);
                _onStop = nullptr;
                cb();
            }
            return;
        }

        Vector2 pos = sprite.GetPosition();
        float targetX = _moveTarget->getSprite().GetPosition().x;
        float dist = std::abs(targetX - pos.x);

        if (dist <= _moveStopDistance)
        {
            _movingToTarget = false;
            _moveTarget = nullptr;
            if (_onStop)
            {
                auto cb = std::move(_onStop);
                _onStop = nullptr;
                cb();
            }
            return;
        }

        float dir = (targetX > pos.x) ? 1.0f : -1.0f;
        pos.x += dir * _moveSpeed * dt;
        sprite.SetPosition(pos);
        return;
    }

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
    if (immortal) return;

    _weaknessAmount   = amount;
    _weaknessDuration = duration;
    _weaknessActive   = true;
    _weaknessOnDone = std::move(onDone);
    // visual
    effectLabel.Show("weaknessEffect", 1.0f);
    effectIcons.Show("weaknessIcon", duration);
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

void BattleEntity::SetScreamEffect(float duration, std::function<void()> onDone)
{
    if (immortal) return;

    _screamDuration = duration;
    _screamActive   = true;
    _screamOnDone = std::move(onDone);
    // перс не может атаковать
    canSelected = false;
    MoveTo(startPosition.x);
    // visual
    effectLabel.Show("screamEffect", 1.0f);
    effectIcons.Show("screamIcon", duration);

    getSprite().SetShaking(true, _screamDuration);
}

void BattleEntity::UpdateScreamEffect(float dt)
{
    if (!_screamActive) return;

    _screamDuration -= dt;

    if (_screamDuration <= 0.0f)
    {
        _screamDuration = 0.0f;
        _screamActive   = false;

        canSelected = true;
        getSprite().SetShaking(false);

        if (_screamOnDone)
        {
            _screamOnDone();
            _screamOnDone = nullptr;
        }
    }
}

void BattleEntity::SetStunEffect(float duration, std::function<void()> onDone)
{
    if (immortal) return;

    _stunDuration = duration;
    _stunActive   = true;
    _stunOnDone = std::move(onDone);
    // перс не может атаковать
    canSelected = false;
    // сохраняем костюм прошлого
    _prevFrameIndex = getSprite().GetSourceRectIndex();

    // останавливаем суку и еще 3 секунды не может атаковать
    _moving = false;
    SetWeaknessEffect(100, _stunDuration + 3.0f);

    // visual
    effectLabel.Show("stunEffect", 1.0f);
    effectIcons.Show("stunIcon", duration);

    getSprite().SetFrameTime(2, _prevFrameIndex, _stunDuration);
    getSprite().SetAlphaFlashing(true);
    // getSprite().SetShaking(true, _stunDuration);
}

void BattleEntity::UpdateStunEffect(float dt)
{
    if (!_stunActive) return;

    _stunDuration -= dt;

    if (_stunDuration <= 0.0f)
    {
        _stunDuration = 0.0f;
        _stunActive   = false;

        canSelected = true;
        _moving = true;

        MoveTo(startPosition.x);

        getSprite().SetShaking(false);
        getSprite().SetAlphaFlashing(false);

        if (_stunOnDone)
        {
            _stunOnDone();
            _stunOnDone = nullptr;
        }
    }
}

void BattleEntity::MoveToTarget(BattleEntity& target, float speed, float stopDistance, std::function<void()> onStop)
{
    _moving = false;

    _movingToTarget = true;
    _moveTarget = &target;
    _moveSpeed = speed;
    _moveStopDistance = stopDistance;
    _onStop = onStop;
}

void BattleEntity::StopMove()
{
    _moving = false;
    _movingToTarget = false;
    _moveTarget = nullptr;
    if (_onStop)
    {
        auto cb = std::move(_onStop);
        _onStop = nullptr;
        cb();
    }
}

// timstop
void BattleEntity::SetTimestopEffect(float duration, std::function<void()> onDone)
{
    if (timestopImmortal) return;

    _timestopDuration = duration;
    _timestopActive   = true;
    _timestopOnDone   = std::move(onDone);

    // save
    _savedMove.moving         = _moving;
    _savedMove.movingToTarget = _movingToTarget;
    _savedMove.moveTargetX    = _moveTargetX;
    _savedMove.moveSpeed      = _moveSpeed;
    _savedMove.moveStopDist   = _moveStopDistance;
    _savedMove.moveTarget     = _moveTarget;
    _savedMove.onStop         = _onStop; 
    _moveStateSaved           = true;

    // stop
    _moving         = false;
    _movingToTarget = false;
    _moveTarget     = nullptr;
    _onStop         = nullptr;

    canSelected = false;

    effectLabel.Show("timestopEffect", duration);
    effectIcons.Show("timestopIcon", duration);
    getSprite().SetAlphaFlashing(true);
}

void BattleEntity::UpdateTimestopEffect(float dt)
{
    if (!_timestopActive) return;

    _timestopDuration -= dt;

    if (_timestopDuration <= 0.0f)
    {
        _timestopDuration = 0.0f;
        _timestopActive   = false;

        canSelected = true;
        getSprite().SetAlphaFlashing(false);

        // continue
        if (_moveStateSaved)
        {
            _moving           = _savedMove.moving;
            _movingToTarget   = _savedMove.movingToTarget;
            _moveTargetX      = _savedMove.moveTargetX;
            _moveSpeed        = _savedMove.moveSpeed;
            _moveStopDistance = _savedMove.moveStopDist;
            _moveTarget       = _savedMove.moveTarget;
            _onStop           = std::move(_savedMove.onStop);
            _moveStateSaved   = false;
        }

        if (_timestopOnDone)
        {
            _timestopOnDone();
            _timestopOnDone = nullptr;
        }
    }
}

// stop abilities
void BattleEntity::InterruptAbility()
{
    // сбрасываем движение
    _moving         = false;
    _movingToTarget = false;
    _moveTarget     = nullptr;
    _onStop         = nullptr;

    // сбрасываем поворот
    _turning       = false;
    _onTurnDone    = nullptr;
    _turnTimesLeft = 0;

    // сбрасываем таймер фрейма спрайта
    getSprite().SetAlphaFlashing(false);
    getSprite().SetShaking(false);
    getSprite().SetFrame(0);

    // сбрасываем touch-колбэки
    ClearOnTouch();

    // trail выключаем
    trail.SetEnabled(false);

    // идём на startPosition
    MoveTo(startPosition.x);
}