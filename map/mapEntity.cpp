#include "mapEntity.h"

bool MapEntity::_drawZones = false;
 
void MapEntity::SetPosition(MapLocation newLoc)
{
    _loc = newLoc;
    MapLocator::PlaceSprite(_sprite, newLoc);
}
 
MapLocation MapEntity::GetPosition() const 
{
    return _loc;
}
 

bool MapEntity::IsPlayerInRange(MapLocation playerPos) const
{
    return MapLocator::GetTileDistance(_loc, playerPos) <= _interactionRadius;
}
 
void MapEntity::TriggerEnter()
{
    if (_onEnter)
        _onEnter();
}
 
void MapEntity::Update(float dt, MapLocation playerPos)
{
    (void)dt;
 
    _sprite.Update(dt);
    _popup.Update(dt);
    _emotion.Update(dt);


    if (!IsPlayerInRange(playerPos))
    {
        _enterConsumed = false;
        return;
    }
 
    // in zone
    if (!_enterConsumed && IsKeyPressed(KEY_ENTER))
    {
        _enterConsumed = true;
        TriggerEnter();
    }
}
 
void MapEntity::Draw()
{
    _sprite.Draw();
 
    _popup.Draw();

    if (_drawZones)
    {
        Vector2 pos = MapLocator::GetWorldPosition(_loc);
        float tileSize = 48.0f;
        float boxSize = (float)(_interactionRadius * 2 + 1) * tileSize;
    
        DrawRectangleLines(
            static_cast<int>(pos.x - boxSize * 0.5f),
            static_cast<int>(pos.y - boxSize * 0.5f),
            static_cast<int>(boxSize),
            static_cast<int>(boxSize),
            Fade(YELLOW, 0.6f)
        );
    }

    _emotion.Draw();
}
