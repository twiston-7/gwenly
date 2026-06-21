#ifndef GWENLY_SUMMONERTIMERINFO_H
#define GWENLY_SUMMONERTIMERINFO_H
#include <optional>

#include "../data/ChampionSummonerSpellData.h"
#include "api/gameclient/data/Player.h"

class SummonerTimerInfo {
    static std::optional<Player> userPlayer;
    static std::optional<std::vector<Player>> enemyPlayers;

    static bool SetUserPlayer(std::vector<Player>& players);
    static bool SetEnemyPlayers(const std::vector<Player>& players);
public:
    static std::optional<std::vector<ChampionSummonerSpellData>> enemySummonerData;
    static bool Fetch();
};

#endif //GWENLY_SUMMONERTIMERINFO_H
