#ifndef GWENLY_SCORES_H
#define GWENLY_SCORES_H

#include <nlohmann/json.hpp>

struct Scores
{
    int assists = 0;
    int creepScore = 0;
    int deaths = 0;
    int kills = 0;
    double wardScore = 0.0;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Scores, assists, creepScore, deaths, kills, wardScore)
};

#endif //GWENLY_SCORES_H
