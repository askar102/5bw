#include "enemyParty.h"

void EnemyParty::Init() {
    for (size_t i = 0; i < 4; ++i) {
        auto character = std::make_unique<BattleEntity>(
            ConfigReader::GetCharacterFromConfig("enemy")
        );
        character->getSprite().SetPosition(this->GetPositionByIndex(i));
        character->facing = FacingDirection::Left;
        Add(std::move(character), i);
    }
}

EnemyParty::EnemyParty() : Party() {}

Vector2 EnemyParty::GetPositionByIndex(size_t index) {
    switch (index) {
        case 0: return {530, 420};

        // todo: is not working right yet
        case 1: return {650, 300};
        case 2: return {680, 415};
        case 3: return {660, 520};
        default: return {0, 0};
    };
}