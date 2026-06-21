#ifndef GWENLY_GAMEVERSION_H
#define GWENLY_GAMEVERSION_H
#include <string>
#include <nlohmann/json.hpp>

class GameVersion {
    public:
        std::string GetGameVersion() {
            auto j = nlohmann::json::parse(json_text);
            return j.at(0).get<std::string>();
        }
};

#endif //GWENLY_GAMEVERSION_H
