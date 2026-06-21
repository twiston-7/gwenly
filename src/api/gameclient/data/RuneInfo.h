#ifndef GWENLY_RUNEINFO_H
#define GWENLY_RUNEINFO_H

#include <nlohmann/json.hpp>

struct RuneInfo
{
    std::string displayName;
    int id = 0;
    std::string rawDescription;
    std::string rawDisplayName;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RuneInfo, displayName, id, rawDescription, rawDisplayName)
};

#endif //GWENLY_RUNEINFO_H
