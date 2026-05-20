#pragma once

#include "party.h"

class EnemyParty : public Party {
public:
    EnemyParty();

    void Init() override;

    Vector2 GetPositionByIndex(size_t index) override;

};