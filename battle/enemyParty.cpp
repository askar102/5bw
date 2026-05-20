void EnemyParty::Init() override {
    // stub
    auto character = std::make_unique<BattleEntity>(ConfigReader::GetCharacterFormConfig("o_o"));
    character->getSprite().SetPosition(this->GetPositionByIndex(0));
    Add(std::move(character), i);

}

EnemyParty::EnemyParty() : Party() {}