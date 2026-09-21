#ifndef GWENLY_CONSTANTS_H
#define GWENLY_CONSTANTS_H
#include <string>

struct Constants {
    // General
    static constexpr LPCWSTR LOCALE = L"en_US";

    // Connection details
    static constexpr LPCWSTR USER_AGENT = L"Gwenly.1.0";

    // Names
    static constexpr std::string_view BLUE_TEAM_INTERNAL_NAME = "ORDER";
    static constexpr std::string_view RED_TEAM_INTERNAL_NAME = "CHAOS";

    // API URLs
    static constexpr LPCWSTR DATA_DRAGON_API_URL = L"ddragon.leagueoflegends.com";
    static constexpr LPCWSTR LEAGUE_GAME_CLIENT_API_URL = L"127.0.0.1";

    // API endpoints
    static constexpr LPCWSTR LEAGUE_VERSIONS_API_ENDPOINT = L"/api/versions.json";
    static constexpr LPCWSTR LEAGUE_ACTIVE_PLAYER_NAME_API_ENDPOINT = L"/liveclientdata/activeplayername";
    static constexpr LPCWSTR LEAGUE_PLAYERLIST_API_ENDPOINT = L"/liveclientdata/playerlist";
    static constexpr LPCWSTR LEAGUE_GAMESTATS_API_ENDPOINT = L"/liveclientdata/gamestats";

    static std::wstring BuildLeagueSummonerDataApiEndpoint(
        const std::wstring& version,
        const std::wstring& locale
    ) {
        return L"/cdn/" + version + L"/data/" + locale + L"/summoner.json";;
    }

    static std::wstring BuildLeagueSummonerSpellImageApiEndpoint(
        const std::wstring& version,
        const std::wstring& summonerSpellId
    ) {
        return L"/cdn/" + version + L"/img/spell/" + summonerSpellId + L".png";
    }

    // Ports
    static constexpr int HTTPS_PORT = 443;
    static constexpr int LEAGUE_GAME_CLIENT_API_PORT = 2999;

    // HTTP Methods
    static constexpr LPCWSTR HTTP_GET = L"GET";
};

#endif //GWENLY_CONSTANTS_H
