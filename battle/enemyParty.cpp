#include "enemyParty.h"

void EnemyParty::Init() {
    // stub
    auto character = std::make_unique<BattleEntity>(ConfigReader::GetCharacterFromConfig("o_o"));
    character->getSprite().SetPosition(this->GetPositionByIndex(0));
    Add(std::move(character), 0);

}

EnemyParty::EnemyParty() : Party() {}

Vector2 EnemyParty::GetPositionByIndex(size_t index) {
    switch (index) {
        case 0: return {530, 420};

        // todo: is not working right yet
        case 1: return {180, 350};
        case 2: return {90, 490};
        case 3: return {50, 340};
        default: return {0, 0};
    };
}