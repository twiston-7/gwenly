#include "api/gameclient/LeagueGameClientApi.h"

#include <windows.h>
#include <winhttp.h>

#include "data/Constants.h"
#include "api/BasicRequest.h"

#pragma comment(lib, "winhttp.lib")

HINTERNET LeagueGameClientApi::gameClientHConnect = nullptr;

bool LeagueGameClientApi::Connect() {
    gameClientHConnect = WinHttpConnect(
        BasicRequest::GetSession(),
        Constants::LEAGUE_GAME_CLIENT_API_URL,
        Constants::LEAGUE_GAME_CLIENT_API_PORT,
        0
    );
    if (!gameClientHConnect) { return false; }
    return true;
}

std::string LeagueGameClientApi::SendRequest(const std::wstring& method, const std::wstring& path)
{
    return BasicRequest::SendBasicRequest(method, path, gameClientHConnect, true);
}

void LeagueGameClientApi::Destroy() {
    WinHttpCloseHandle(gameClientHConnect);
    WinHttpCloseHandle(BasicRequest::GetSession());
}
