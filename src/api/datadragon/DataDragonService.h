#ifndef GWENLY_DATADRAGONSERVICE_H
#define GWENLY_DATADRAGONSERVICE_H
#include <string>
#include <windows.h>
#include <winhttp.h>
#include <nlohmann/json.hpp>

#include "data/Constants.h"
#include "api/BasicRequest.h"

class DataDragonService {
    static std::unordered_map<std::string, unsigned int> GetCooldownMap() {
        static std::unordered_map<std::string, unsigned int> cooldownMap = [] {
            const std::string response = BasicRequest::SendBasicRequest(
                Constants::HTTP_GET,
                Constants::BuildLeagueSummonerDataApiEndpoint(GetLatestLeagueVersion(), Constants::LOCALE),
                GetConnection(),
                false
            );

            auto jsonData = nlohmann::json::parse(response);

            const nlohmann::json& spells = jsonData["data"];

            auto returnMap = std::unordered_map<std::string, unsigned int>();

            for (auto& [key, spell] : spells.items()) {
                auto name = spell["name"].get<std::string>();
                auto cooldownString = spell["cooldownBurn"].get<std::string>();
                auto const cooldown = static_cast<unsigned int>(std::stoul(cooldownString));

                returnMap[name] = cooldown;
            }

            return returnMap;
        }();
        return cooldownMap;
    }

    static HINTERNET GetConnection() {
        static HINTERNET dataDragonConnection = WinHttpConnect(
            BasicRequest::GetSession(),
            Constants::DATA_DRAGON_API_URL,
            Constants::HTTPS_PORT,
            0
        );
        return dataDragonConnection;
    }
public:
    static std::wstring GetLatestLeagueVersion();
    static unsigned int GetCooldownForSummonerSpell(const std::string &displayName);
};


#endif //GWENLY_DATADRAGONSERVICE_H
