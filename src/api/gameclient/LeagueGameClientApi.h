#ifndef GWENLY_LEAGUEGAMECLIENTAPI_H
#define GWENLY_LEAGUEGAMECLIENTAPI_H

#include <string>
#include <windows.h>
#include <winhttp.h>

struct PlayerRunes {
    static std::string userRiotId;
};

class LeagueGameClientApi {
public:
    static bool Connect();
    static std::string SendRequest(const std::wstring& method, const std::wstring& path);
    static void Destroy();

private:
    static HINTERNET gameClientHConnect;
};

#endif //GWENLY_LEAGUEGAMECLIENTAPI_H
