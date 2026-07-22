#include "npc.h"
#include "mapEntity.h"

void Npc::MoveTo(MapLocation target, float speed, std::function<void()> onArrive)
{
    _target = target;
    _speed = speed;
    _onArrive = std::move(onArrive);
    _moving = true;
}
 
void Npc::StopMove()
{
    _moving   = false;
    _onArrive = nullptr;
}
 
void Npc::UpdateMove(float dt)
{
    if (!_moving) return;

    Vector2 pos = MapLocator::GetWorldPosition(_loc); 
    Vector2 targetPos = MapLocator::GetWorldPosition(_target);
    float dx = targetPos.x - pos.x;
    float dy = targetPos.y - pos.y;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist <= ARRIVE_THRESHOLD)
    {
        SetPosition(_target);
        _moving = false;

        if (_onArrive)
        {
            auto cb = std::move(_onArrive);
            _onArrive = nullptr;
            cb();
        }
        return;
    }

    float step = _speed * dt;
    if (step > dist) step = dist;

    _sprite.SetPosition({
        pos.x + (dx / dist) * step,
        pos.y + (dy / dist) * step
    });
}
 
void Npc::Update(float dt, MapLocation playerPos)
{
    UpdateMove(dt);                                                                                  
 
    // MapEntity::Update(dt, playerPos);

    (void)dt;
 
    _sprite.Update(dt);
    _popup.Update(dt);
    _emotion.Update(dt);

    if (_waitForSecondEnter && IsKeyPressed(KEY_ENTER)) {
        if (_onSecondEnter) {
            _onSecondEnter();
        }

        _waitForSecondEnter = false; 
    }

    if (!IsPlayerInRange(playerPos))
    {
        _waitForSecondEnter = false;
        _enterConsumed = false;
        return;
    }
 
    // in zone
    if (!_enterConsumed && IsKeyPressed(KEY_ENTER))
    {
        _waitForSecondEnter = true;
        _enterConsumed = true;

        if (!_onFirstEnter && _secondEnterEnabled) {
            GetEmotionPopUp().Show(EmotionType::Confusion, 3.0f);
        }

        if (_onFirstEnter) {
            _onFirstEnter();
        }
    }
}

void Npc::Draw()
{
    MapEntity::Draw();

    _emotion.Draw();
}

// в Npc назначает onFirstEnter!!!!
void Npc::SetOnEnter(std::function<void()> cb) 
{
    SetOnFirstEnter(cb);
}

// в Npc вызывает onFirstEnter!!!!
void Npc::TriggerEnter() 
{
    if (_onFirstEnter) {
        _onFirstEnter();
    }
}