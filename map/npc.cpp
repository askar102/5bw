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
    float dist = std::sqrt(dx * dx + dy * dy);

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
 
    MapEntity::Update(dt, playerPos);
}
