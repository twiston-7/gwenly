#ifndef GWENLY_ITEM_H
#define GWENLY_ITEM_H

#include <nlohmann/json.hpp>

struct Item
{
    bool canUse = false;
    bool consumable = false;
    int count = 0;
    std::string displayName;
    int itemID = 0;
    int price = 0;
    std::string rawDescription;
    std::string rawDisplayName;
    int slot = 0;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Item, canUse, consumable, count, displayName,
        itemID, price, rawDescription, rawDisplayName, slot)
};

#endif //GWENLY_ITEM_H
