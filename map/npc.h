#pragma once

#include "mapEntity.h"

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"
#include <functional>
#include <mutex>

enum class NpcMovementMode {
    Idle,
    Patrol
};

class Npc : public MapEntity {
public:
    Npc() { _emotion.Init(&_sprite); }

    void MoveTo(MapLocation target, float speed = 100.0f, std::function<void()> onArrive = nullptr);

    void StopMove();

    bool IsMoving() const { return _moving; }

    void Update(float dt, MapLocation playerPos) override;
    void Draw() override;

    bool GetCollide() { return _collide; }
    void SetCollide(bool newValue) { _collide = newValue; }

    Emotion& GetEmotionPopUp() { return _emotion; }
    void SetOnFirstEnter(std::function<void()> onFirstEnter = nullptr) { _onFirstEnter = onFirstEnter; } 
    void SetOnSecondEnter(bool enabled, std::function<void()> onSecondEnter = nullptr) 
    { 
        if (enabled) {
            _onSecondEnter = onSecondEnter; 
        } else _secondEnterEnabled = false;
    }

    void SetOnEnter(std::function<void()> cb) override;
    void TriggerEnter() override;

private:
    void UpdateMove(float dt);

    bool _moving = false;
    MapLocation _target = {0, 0, 0, 0};
    float _speed = 100.0f;
    std::function<void()> _onArrive;

    bool _collide = true;

    static constexpr float ARRIVE_THRESHOLD = 2.0f;

    bool _canTalk = true;
    bool _aggressive = false;
    NpcMovementMode _movementMode = NpcMovementMode::Idle;
    int32_t _territoryRadius = 3;

    bool _waitForSecondEnter = false;
    Emotion _emotion;

    std::function<void()> _onFirstEnter = nullptr;
    std::function<void()> _onSecondEnter = nullptr;

    bool _secondEnterEnabled = true;
};