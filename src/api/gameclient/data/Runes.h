#ifndef GWENLY_RUNES_H
#define GWENLY_RUNES_H

#include <nlohmann/json.hpp>
#include "api/gameclient/data/RuneInfo.h"

struct Runes
{
    RuneInfo keystone;
    RuneInfo primaryRuneTree;
    RuneInfo secondaryRuneTree;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Runes, keystone, primaryRuneTree, secondaryRuneTree)
};

#endif //GWENLY_RUNES_H
