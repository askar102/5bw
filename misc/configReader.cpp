#include "configReader.h"

using json = nlohmann::json;

std::array<std::string, 4> ConfigReader::GetPartyFromConfig()
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