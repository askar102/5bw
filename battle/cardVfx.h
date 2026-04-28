#pragma once

#include "battleEntity.h"
#include "vfx.h"

class CardVfx : public Vfx {
public:
    CardVfx(Vector2 position, float lifetime, float rotation, Texture2D* texture, BattleEntity& target);

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;
    bool IsFinished() const override;

private:
    /**
     * TODO: change _target type to std::weak_ptr
     * 
     */
    BattleEntity* _target;
    bool _hitTarget = false;
    bool _leftScreen = false;
};
    
