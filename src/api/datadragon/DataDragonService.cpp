#include "DataDragonService.h"

#include <nlohmann/json.hpp>

#include "data/Constants.h"

std::wstring to_wstring(const std::string& str)
{
    if (str.empty()) return L"";

    int size_needed = MultiByteToWideChar(
        CP_UTF8, 0,
        str.c_str(), (int)str.size(),
        nullptr, 0
    );

    std::wstring result(size_needed, 0);

    MultiByteToWideChar(
        CP_UTF8, 0,
        str.c_str(), (int)str.size(),
        &result[0], size_needed
    );

    return result;
}

std::wstring DataDragonService::GetLatestLeagueVersion() {
    static auto leagueVersion = [] {
            const std::string response = BasicRequest::SendBasicRequest(
                Constants::HTTP_GET,
                Constants::LEAGUE_VERSIONS_API_ENDPOINT,
                GetConnection(),
                false
            );

        auto j = nlohmann::json::parse(response.c_str());
        return j.at(0).get<std::string>(); // First entry = latest version
    }();

    return to_wstring(leagueVersion);
}

unsigned int DataDragonService::GetCooldownForSummonerSpell(const std::string &displayName) {
    return GetCooldownMap().at(displayName);
}

