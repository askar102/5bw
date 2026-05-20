void PlayerParty::Init() override {
    std::array<std::string, 4> configParty = ConfigReader::GetPlayerPartyFromConfig();

    for (size_t i = 0; i < configParty.size(); ++i)
    {
        std::string str = configParty[i];

        if (!str.empty())
        {
            auto character = std::make_unique<BattleEntity>(ConfigReader::GetCharacterFromConfig(str));

            character->getSprite().SetPosition(this->GetPositionByIndex(i));

            Add(std::move(character), i);
        }
    }
}

PlayerParty::PlayerParty() : Party() {}