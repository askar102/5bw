#include "mapItem.h"
#include "item/item.h"
#include "item/itemManager.h"

void MapItem::CheckCollision(const SpriteV2& playerSprite) {
    if (_anchor || _icon.IsFadingOut()) return; 

    if (CheckCollisionRecs(_icon.GetRect(), playerSprite.GetRect())) {
        _icon.SetAlpha(0.5f);
        _anchor = &playerSprite;
    }
}

void MapItem::Update(float dt, Player& player) {
    if (!_destoyed) {
        _icon.Update(dt);
        CheckCollision(player.getSprite());

        if (_anchor) 
        {
            Inventory::Add(_id);
            player.EquipItem({_id, ItemManager::GetInfo(_id)});
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