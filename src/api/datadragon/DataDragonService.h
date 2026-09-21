#ifndef GWENLY_DATADRAGONSERVICE_H
#define GWENLY_DATADRAGONSERVICE_H
#include <complex.h>
#include <string>
#include <windows.h>
#include <winhttp.h>
#include <nlohmann/json.hpp>

#include "data/Constants.h"
#include "api/BasicRequest.h"
#include "data/SummonerSpellInfo.h"

class DataDragonService {
    [[nodiscard]] static std::unordered_map<std::string, unsigned int> GetCooldownMap();
    [[nodiscard]] static std::vector<SummonerSpellInfo> GetSummonerSpellData();

    static HINTERNET GetDataDragonConnection() {
        static HINTERNET dataDragonConnection = WinHttpConnect(
            BasicRequest::GetSession(),
            Constants::DATA_DRAGON_API_URL,
            Constants::HTTPS_PORT,
            0
        );
        return dataDragonConnection;
    }
public:
    [[nodiscard]] static std::wstring GetLatestLeagueVersion();
    [[nodiscard]] static unsigned int GetCooldownForSummonerSpell(const std::string &displayName);
    [[nodiscard]] static std::string SummonerSpellDisplayNameToId(const std::string &displayName, const std::string &gameMode);

    [[nodiscard]] static std::string GetSummonerSpellImageBytes(const std::string &id);
};


#endif //GWENLY_DATADRAGONSERVICE_H
