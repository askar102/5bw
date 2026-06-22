#include "mapItem.h"

void MapItem::CheckCollision(const SpriteV2& playerSprite) {
    if (_anchor || _icon.IsFadingOut()) return; 

    if (CheckCollisionRecs(_icon.GetRect(), playerSprite.GetRect())) {
        _icon.SetAlpha(0.5f);
        _anchor = &playerSprite;
    }
}

void MapItem::Update(float dt, const SpriteV2& playerSprite) {
    if (!_destoyed) {
        _icon.Update(dt);
        CheckCollision(playerSprite);

        if (_anchor) 
        {
            _bringAnimationTimer += dt;

            _icon.SetPosition({_anchor->GetPosition().x, _anchor->GetPosition().y - 50.0f});


            if (_bringAnimationTimer >= _bringAnimationDuration && !_icon.IsFadingOut()) {
                _icon.FadeOut(3.0f, [this] () {
                    _bringAnimationTimer = 0.0f;
                    // _anchor = nullptr;
                    _icon.SetAlpha(0.0f);

                    _destoyed = true;
                });
            }
        }
    }
}

void MapItem::Draw() {
    _icon.Draw();
}