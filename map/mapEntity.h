#pragma once

#include <functional>

#include "../raylib/raylib.h"

#include "../entities/spriteV2.h"

#include "../dialog/dialogPopup.h"

#include "mapLocation.h"


#include "../dialog/emotion.h"

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

    void SetInteractionRadius(int32_t tiles) { _interactionRadius = tiles; }
    int32_t GetInteractionRadius() const { return _interactionRadius; }

    virtual void SetOnEnter(std::function<void()> cb) { _onEnter = std::move(cb); }

    virtual void TriggerEnter();

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
                 
    int32_t _interactionRadius = 2;
    std::function<void()> _onEnter;

    bool _enterConsumed = false;

    // debug
    static bool _drawZones;

    DialogPopup _popup;
};