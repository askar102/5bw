#include "enemyParty.h"

void EnemyParty::Init() {
    // stub
    auto character = std::make_unique<BattleEntity>(ConfigReader::GetCharacterFromConfig("o_o"));
    character->getSprite().SetPosition(this->GetPositionByIndex(0));
    Add(std::move(character), 0);

}

EnemyParty::EnemyParty() : Party() {}