#include "mapEntity.h"

bool MapEntity::_drawZones = false;
 
void MapEntity::SetPosition(Vector2 pos)
{
    _sprite.SetPosition(pos);
}
 
Vector2 MapEntity::GetPosition() const
{
    return _sprite.GetPosition();
}
 
bool MapEntity::IsPlayerInRange(Vector2 playerPos) const
{
    Vector2 myPos = GetPosition();
    float dx = playerPos.x - myPos.x;
    float dy = playerPos.y - myPos.y;
    return (dx * dx + dy * dy) <= (_interactionRadius * _interactionRadius);
}
 
void MapEntity::TriggerEnter()
{
    if (_onEnter)
        _onEnter();
}
 
void MapEntity::Update(float dt, Vector2 playerPos)
{
    (void)dt;
 
    _sprite.Update(dt);
    _popup.Update(dt);


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
        DrawCircleLines(
            static_cast<int>(GetPosition().x),
            static_cast<int>(GetPosition().y),
            _interactionRadius,
            Fade(YELLOW, 0.6f)
        );
    }
}
