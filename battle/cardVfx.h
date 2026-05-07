/**
 * @file cardVfx.h
 * @author askar102
 * @brief Card bullet vfx
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include "battleEntity.h"
#include "vfx.h"

class CardVfx : public Vfx {
public:
    CardVfx(Vector2 position, 
            float lifetime, 
            float rotation, 
            TextureResource* textureResource, 
            BattleEntity& target, 
            // peaceful - will use EnemyHitAnimation or not?
            bool peaceful = true, 
            bool animated = true);

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;
    bool IsFinished() const override;

    bool Hitted();

private:
    /**
     * TODO: change _target type to std::weak_ptr
     * 
     */
    BattleEntity* _target;
    bool _leftScreen = false;

    /**
     * @brief will use EnemyHitAnimation or not?
     * 
     * @ref cardVfx.cpp, line ~35
     */
    bool _peaceful = true;

    /**
     * @ref cardVfx.cpp line ~42
     * 
     * TODO: Make it in different place
     */
     const int _DAMAGE_OF_ONE_CARD = 2;

    bool _animated = true;
};
    
