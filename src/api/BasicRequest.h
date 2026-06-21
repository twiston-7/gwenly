#ifndef GWENLY_BASICREQUEST_H
#define GWENLY_BASICREQUEST_H

#include <string>
#include <windows.h>
#include <winhttp.h>

#include "data/Constants.h"

class BasicRequest {
public:
    static HINTERNET GetSession()
    {
        static HINTERNET hInternet = WinHttpOpen(
            Constants::USER_AGENT,
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0
        );

        return hInternet;
    }

    static std::string SendSingleRequest(
        const std::wstring &url,
        int port,
        const std::wstring &method,
        const std::wstring &path
    );

    static std::string SendBasicRequest(
        const std::wstring &method,
        const std::wstring &path,
        HINTERNET hConnect,
        bool disableCertValidation = false
    );

    static std::string GetBody(const HINTERNET &hRequest);
};


#endif //GWENLY_BASICREQUEST_H
