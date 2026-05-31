#pragma once

#include <functional>

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

class MapEntity {
public:
    MapEntity() = default;
    virtual ~MapEntity() = default;

    SpriteV2& GetSprite()             { return _sprite; }
    const SpriteV2& GetSprite() const { return _sprite; }

    virtual void    SetPosition(Vector2 pos);
    Vector2         GetPosition() const;

    void SetInteractionRadius(float radius) { _interactionRadius = radius; }
    float GetInteractionRadius() const      { return _interactionRadius;   }

    void SetOnEnter(std::function<void()> cb) { _onEnter = std::move(cb); }

    void TriggerEnter();

    bool IsPlayerInRange(Vector2 playerPos) const;
    
    // core
    virtual void Update(float dt, Vector2 playerPos);
    virtual void Draw();
    
    static void SetDrawZones(bool value) { _drawZones = value; }
    static bool GetDrawZones()           { return _drawZones;  }

protected:
    SpriteV2 _sprite;

    float _interactionRadius = 80.0f;
    std::function<void()> _onEnter;

    bool _enterConsumed = false;

    // debug
    static bool _drawZones;
};