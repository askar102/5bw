#pragma once

#include <functional>

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

#include "../dialog/dialogPopup.h"

#include "mapLocation.h"

class MapState;
class Player;

class MapEntity {
public:
    MapEntity() = default;
    virtual ~MapEntity() = default;

    SpriteV2& GetSprite() { return _sprite; }
    const SpriteV2& GetSprite() const { return _sprite; }

    virtual void  SetPosition(MapLocation loc);
    MapLocation GetPosition() const;

    void SetInteractionRadius(float radius) { _interactionRadius = radius; }
    float GetInteractionRadius() const { return _interactionRadius;   }

    void SetOnEnter(std::function<void()> cb) { _onEnter = std::move(cb); }

    void TriggerEnter();

    bool IsPlayerInRange(MapLocation playerPos) const;
    
    // core
    virtual void Update(float dt, MapLocation playerPos);
    virtual void Draw();
    
    static void SetDrawZones(bool value) { _drawZones = value; }
    static bool GetDrawZones() { return _drawZones;  }

    // dialog
    DialogPopup& GetDialogPopUp() { return _popup; }

protected:
    SpriteV2 _sprite;

    MapLocation _loc = {0, 0, 0, 0};
                 
    float _interactionRadius = 80.0f;
    std::function<void()> _onEnter;

    bool _enterConsumed = false;

    // debug
    static bool _drawZones;

    DialogPopup _popup;
};