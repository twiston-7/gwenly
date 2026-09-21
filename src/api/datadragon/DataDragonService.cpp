#include "DataDragonService.h"

#include <nlohmann/json.hpp>

#include "data/Constants.h"
#include "data/SummonerSpellInfo.h"

static std::wstring to_wstring(const std::string& str)
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

std::vector<SummonerSpellInfo> DataDragonService::GetSummonerSpellData() {
    const std::string response = BasicRequest::SendBasicRequest(
        Constants::HTTP_GET,
        Constants::BuildLeagueSummonerDataApiEndpoint(GetLatestLeagueVersion(), Constants::LOCALE),
        GetDataDragonConnection(),
        false
    );

    auto jsonData = nlohmann::json::parse(response);

    auto spellMap = jsonData["data"].get<std::unordered_map<std::string, SummonerSpellInfo>>();
    static std::vector<SummonerSpellInfo> result = [spellMap] {
        std::vector<SummonerSpellInfo> returnVector;
        returnVector.reserve(spellMap.size());

        std::transform(spellMap.begin(), spellMap.end(), std::back_inserter(returnVector),
            [](const auto& pair) { return pair.second; });
        return returnVector;
    }();

    return result;
}

std::string DataDragonService::SummonerSpellDisplayNameToId(const std::string &displayName, const std::string &gameMode) {
    const bool wantJade = gameMode.find("JADE") != std::string::npos;
    OutputDebugStringW((L"wantJade?: " + std::to_wstring(wantJade) + L"\n").c_str());

    const auto summonerSpellInfo = GetSummonerSpellData();
    std::vector<const SummonerSpellInfo *> matches;

    for (auto& spell : summonerSpellInfo) {
        if (spell.name == displayName) { matches.push_back(&spell); }
    }

    OutputDebugStringW((L"Found " + std::to_wstring(matches.size()) + L" matches for " + to_wstring(displayName) + L"\n").c_str());

    if (matches.empty()) { return ""; }
    if (matches.size() == 1) { return matches.front()->id; }

    for (auto* spell : matches) {
        if (spell->id.find("Jade") != std::string::npos == wantJade) { return spell->id; }
    }

    return matches.front()->id;
}

std::unordered_map<std::string, unsigned int> DataDragonService::GetCooldownMap() {
    auto summonerSpellInfo = GetSummonerSpellData();

    static std::unordered_map<std::string, unsigned int> cooldownMap = [summonerSpellInfo] {
        auto returnMap = std::unordered_map<std::string, unsigned int>();

        for (auto& spell : summonerSpellInfo) {
            auto const cooldown = static_cast<unsigned int>(std::stoul(spell.cooldownBurn));

            returnMap[spell.name] = cooldown;
        }

        return returnMap;
    }();

    return cooldownMap;
}

std::wstring DataDragonService::GetLatestLeagueVersion() {
    static auto leagueVersion = [] {
            const std::string response = BasicRequest::SendBasicRequest(
                Constants::HTTP_GET,
                Constants::LEAGUE_VERSIONS_API_ENDPOINT,
                GetDataDragonConnection(),
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

std::string DataDragonService::GetSummonerSpellImageBytes(const std::string &id) {
    return BasicRequest::SendBasicRequest(
        Constants::HTTP_GET,
        Constants::BuildLeagueSummonerSpellImageApiEndpoint(GetLatestLeagueVersion(), to_wstring(id)),
        GetDataDragonConnection(),
        false
    );
}
