#ifndef GWENLY_PLAYER_H
#define GWENLY_PLAYER_H

#include "api/gameclient/data/Runes.h"
#include "api/gameclient/data/Scores.h"
#include "api/gameclient/data/SummonerSpells.h"
#include "api/gameclient/data/Item.h"

#include <nlohmann/json.hpp>

struct Player
{
    std::string championName;
    bool isBot = false;
    bool isDead = false;
    std::vector<Item> items;
    int level = 0;
    std::string position;
    std::string rawChampionName;
    std::string rawSkinName;
    double respawnTimer = 0.0;
    std::string riotId;
    std::string riotIdGameName;
    std::string riotIdTagLine;
    Runes runes;
    Scores scores;
    int skinID = 0;
    std::string skinName;
    std::string summonerName;
    SummonerSpells summonerSpells;
    std::string team;
    bool dataUnavailable = false;

    friend void from_json(const nlohmann::json& j, Player& p)
    {
        j.at("championName").get_to(p.championName);
        j.at("isBot").get_to(p.isBot);
        j.at("isDead").get_to(p.isDead);
        j.at("level").get_to(p.level);
        j.at("position").get_to(p.position);
        j.at("rawChampionName").get_to(p.rawChampionName);
        j.at("rawSkinName").get_to(p.rawSkinName);
        j.at("respawnTimer").get_to(p.respawnTimer);
        j.at("riotId").get_to(p.riotId);
        j.at("riotIdGameName").get_to(p.riotIdGameName);
        j.at("riotIdTagLine").get_to(p.riotIdTagLine);
        j.at("skinID").get_to(p.skinID);
        j.at("skinName").get_to(p.skinName);
        j.at("summonerName").get_to(p.summonerName);
        j.at("team").get_to(p.team);

        if (const auto& itemsJ = j.at("items"); itemsJ.is_array())
            p.items = itemsJ.get<std::vector<Item>>();
        else
            p.dataUnavailable = true;

        if (const auto& runesJ = j.at("runes"); runesJ.is_object() && !runesJ.contains("error"))
            p.runes = runesJ.get<Runes>();
        else
            p.dataUnavailable = true;

        if (const auto& scoresJ = j.at("scores"); scoresJ.is_object() && !scoresJ.contains("error"))
            p.scores = scoresJ.get<Scores>();
        else
            p.dataUnavailable = true;

        if (const auto& spellsJ = j.at("summonerSpells"); spellsJ.is_object() && !spellsJ.contains("error"))
            p.summonerSpells = spellsJ.get<SummonerSpells>();
        else
            p.dataUnavailable = true;
    }

    friend void to_json(nlohmann::json& j, const Player& p)
    {
        j = nlohmann::json{
            {"championName", p.championName}, {"isBot", p.isBot},
            {"isDead", p.isDead}, {"items", p.items}, {"level", p.level},
            {"position", p.position}, {"rawChampionName", p.rawChampionName},
            {"rawSkinName", p.rawSkinName}, {"respawnTimer", p.respawnTimer},
            {"riotId", p.riotId}, {"riotIdGameName", p.riotIdGameName},
            {"riotIdTagLine", p.riotIdTagLine}, {"runes", p.runes},
            {"scores", p.scores}, {"skinID", p.skinID}, {"skinName", p.skinName},
            {"summonerName", p.summonerName}, {"summonerSpells", p.summonerSpells},
            {"team", p.team}
        };
    }
};

#endif //GWENLY_PLAYER_H
