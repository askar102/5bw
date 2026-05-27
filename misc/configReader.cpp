#include "configReader.h"

using json = nlohmann::json;

std::array<std::string, 4> ConfigReader::GetPlayerPartyFromConfig()
{
    std::array<std::string, 4> party = { "", "", "", "" };

    std::ifstream file("config.json");

    if (!file.is_open())
    {
        TraceLog(TraceLogLevel::LOG_WARNING, "[configReader] Cant open config.json!!!");

        return party;
    }

    json config;
    file >> config;

    if (!config.contains("playerParty") || !config["playerParty"].is_array())
    {
        TraceLog(TraceLogLevel::LOG_WARNING, "[configReader] playerParty in config.json is not array or I dont see it");
        
        return party;
    }

    const json& playerParty = config["playerParty"];

    for (size_t i = 0; i < playerParty.size() && i < 4; ++i)
    {
        if (playerParty[i].is_string())
        {
            party[i] = playerParty[i].get<std::string>();
        }
    }

    return party;
}


BattleEntity ConfigReader::GetCharacterFromConfig(std::string name)
{
    BattleEntity character(name, 100, false, false, {});

    std::ifstream file("config.json");

    if (!file.is_open())
    {
        TraceLog(LOG_WARNING, "[configReader] I cant open config.json!!!!!");
        return character;
    }

    json config;
    file >> config;

    if (!config.contains("characters") || !config["characters"].is_array())
    {
        TraceLog(LOG_WARNING, "[configReader] I dont see characters-list or is not array");
        return character;
    }

    const json& charactersList = config["characters"];

    for (size_t i = 0; i < charactersList.size(); ++i)
    {
        const auto& characterInfo = charactersList[i];

        if (!characterInfo.contains("name") || !characterInfo["name"].is_string())
            continue;

        std::string characterName = characterInfo["name"];

        if (characterName != name)
            continue;

        character = BattleEntity(
            characterName,
            characterInfo.value("maxHp", 100),
            characterInfo.value("isEnemy", false),
            characterInfo.value("canSelected", true),
            {}
        );

        if (characterInfo.contains("abilities") && characterInfo["abilities"].is_array())
        {
            for (const auto& ab : characterInfo["abilities"])
            {
                character.abilities.push_back(
                    std::make_unique<Ability>(
                        ab.value("name", ""),
                        ab.value("damage", 0),
                        ab.value("heal", 0),
                        ParseAbilityType(ab.value("type", ""))
                    )
                );
            }
        }

        return character;
    }

    TraceLog(LOG_WARNING, "[configReader] I cant find this character: %s", name.c_str());
    return character;
}

AbilityType ConfigReader::ParseAbilityType(const std::string& type)
{
    if (type == "bullet_default" || type == "bullet")
        return AbilityType::BulletDefault;

    if (type == "bullet_splash")
        return AbilityType::BulletSplash;

    if (type == "unique")
        return AbilityType::Unique;

    return AbilityType::Melee;
}