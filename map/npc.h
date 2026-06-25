#pragma once

#include "mapEntity.h"

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

class Npc : public MapEntity {
public:
    Npc() = default;

    void MoveTo(MapLocation target, float speed = 100.0f, std::function<void()> onArrive = nullptr);

    void StopMove();

    bool IsMoving() const { return _moving; }

    void Update(float dt, MapLocation playerPos) override;

private:
    void UpdateMove(float dt);
 
    bool _moving = false;
    MapLocation _target = {0, 0, 0, 0};
    float _speed = 100.0f;
    std::function<void()> _onArrive;
 
    static constexpr float ARRIVE_THRESHOLD = 2.0f;
};