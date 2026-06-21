#include "SummonerTimerInfo.h"

#include <nlohmann/json.hpp>

#include "api/gameclient/LeagueGameClientApi.h"
#include "api/datadragon/DataDragonService.h"
#include "data/Constants.h"
#include "data/ChampionSummonerSpellData.h"

std::optional<Player> SummonerTimerInfo::userPlayer;
std::optional<std::vector<Player>> SummonerTimerInfo::enemyPlayers;
std::optional<std::vector<ChampionSummonerSpellData>> SummonerTimerInfo::enemySummonerData;

bool SummonerTimerInfo::SetUserPlayer(std::vector<Player> &players) {
    std::string playerNameResponse =
    LeagueGameClientApi::SendRequest(Constants::HTTP_GET, Constants::LEAGUE_ACTIVE_PLAYER_NAME_API_ENDPOINT);
    const nlohmann::json nameJson = nlohmann::json::parse(playerNameResponse);
    auto activePlayerName = nameJson.get<std::string>();

    if (!playerNameResponse.data()) {
        return false;
    }

    const auto it = std::find_if(players.begin(), players.end(),
    [&activePlayerName](const Player& p) { return p.riotId == activePlayerName; });

    if (it != players.end()) {
        userPlayer = std::move(*it);
        return true;
    }

    return false;
}

constexpr bool IsKnownTeam(const std::string &teamName) {
    return teamName == Constants::BLUE_TEAM_INTERNAL_NAME ||
        teamName == Constants::RED_TEAM_INTERNAL_NAME;
}

bool SummonerTimerInfo::SetEnemyPlayers(const std::vector<Player> &players) {
    enemyPlayers.emplace();

    for (auto& player : players) {
        if (IsKnownTeam(player.team) && player.team != userPlayer->team) {
            enemyPlayers.value().push_back(player);
        }
    }

    return enemyPlayers.has_value();
}

bool SummonerTimerInfo::Fetch() {
    if (!LeagueGameClientApi::Connect()) {
        OutputDebugStringA("Failed to connect to the League Game Client API. Is the game running?\n");
        return false;
    }

    std::string playerListResponse =
        LeagueGameClientApi::SendRequest(
            Constants::HTTP_GET,
            Constants::LEAGUE_PLAYERLIST_API_ENDPOINT
        );

    if (playerListResponse.empty()) {
        OutputDebugStringA("Could not fetch playerlist. Is the game running?\n");
        return false;
    }

    nlohmann::json j = nlohmann::json::parse(playerListResponse);
    auto players = j.get<std::vector<Player>>();
    players.erase(std::remove_if(players.begin(), players.end(),
        [](const Player& p) { return p.dataUnavailable; }), players.end());

    if (!userPlayer) {
        if (!SetUserPlayer(players)) {
            // Probably not in game
            OutputDebugStringA("Could not fetch user player. Is the game running?\n");
            return false;
        }
    }

    if (!SetEnemyPlayers(players)) {
        OutputDebugStringA("No enemy summoners with valid team found\n");
        return false;
    }

    enemySummonerData.emplace();

    for (const auto &player : enemyPlayers.value()) {
        ChampionSummonerSpellData summonerData{
            player.championName,
            SummonerSpellData(
                player.summonerSpells.summonerSpellOne.displayName,
                DataDragonService::GetCooldownForSummonerSpell(player.summonerSpells.summonerSpellOne.displayName)
            ),
            SummonerSpellData(
                player.summonerSpells.summonerSpellTwo.displayName,
                DataDragonService::GetCooldownForSummonerSpell(player.summonerSpells.summonerSpellTwo.displayName)
            )
        };
        enemySummonerData->push_back(summonerData);
    }

    return true;
}
