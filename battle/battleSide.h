#pragma once

// Какая сторона поля получает урон от снаряда / эффекта.
enum class DamageableSide {
    Player,
    Enemy
};

inline DamageableSide DamageSideForCaster(bool casterIsEnemy)
{
    return casterIsEnemy ? DamageableSide::Player : DamageableSide::Enemy;
}
