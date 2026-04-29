#pragma once

#include "battleEntity.h"
#include "vfx.h"

class CardVfx : public Vfx {
public:
    /**
     * @brief Construct a new Card Vfx object
     * 
     * @param position position of object
     * @param lifetime lifetime of object
     * @param rotation rotation of object
     * @param texture texture
     * @param target target object
     * @param _peaceful will use EnemyHitAnimation or not? default value: true
     */
    CardVfx(Vector2 position, float lifetime, float rotation, Texture2D* texture, BattleEntity& target, bool _peaceful = true);

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

    /**
     * @brief will use EnemyHitAnimation or not?
     * 
     * @ref cardVfx.cpp, line ~35
     */
    bool _peaceful = true;
};
    
