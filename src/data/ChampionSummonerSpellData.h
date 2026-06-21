#ifndef GWENLY_SUMMONERSPELLDATA_H
#define GWENLY_SUMMONERSPELLDATA_H

#include <string>
#include <chrono>
#include <utility>

class SummonerSpellData {
    std::chrono::steady_clock::time_point usableAgainAt;

public:
    SummonerSpellData(std::string displayName, const unsigned int cooldown)
        : displayName(std::move(displayName)), cooldown(cooldown) {}

    const std::string displayName;
    unsigned int cooldown;

    void StartCooldown() { usableAgainAt = std::chrono::steady_clock::now() + std::chrono::seconds(cooldown); }
    [[nodiscard]] bool IsUsable() const { return std::chrono::steady_clock::now() >= usableAgainAt; }
};

struct ChampionSummonerSpellData {
    const std::string championName;
    SummonerSpellData summonerSpellOne;
    SummonerSpellData summonerSpellTwo;
};

#endif //GWENLY_SUMMONERSPELLDATA_H
