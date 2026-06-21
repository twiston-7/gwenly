#include "BasicRequest.h"

#include <string>
#include <windows.h>
#include <winhttp.h>

std::string BasicRequest::GetBody(const HINTERNET &hRequest) {
    std::string result;
    DWORD available = 0;

    while (WinHttpQueryDataAvailable(hRequest, &available) && available > 0)
    {
        const size_t startSize = result.size();
        result.resize(startSize + available);

        DWORD read = 0;

        if (!WinHttpReadData(hRequest, result.data() + startSize, available, &read) || read == 0)
            break;

        if (read < available) {
            result.resize(startSize + read);
        }
    }

    return result;
}

std::string BasicRequest::SendSingleRequest(
        const std::wstring &url, const int port, const std::wstring &method, const std::wstring &path
    ) {

    HINTERNET hConnect = WinHttpConnect(GetSession(), url.c_str(), port, 0);

    auto returnValue = SendBasicRequest(method, path, hConnect);
    WinHttpCloseHandle(hConnect);
    return returnValue;
}

std::string BasicRequest::SendBasicRequest(
        const std::wstring &method,
        const std::wstring &path,
        HINTERNET hConnect,
        bool disableCertValidation
    ) {
    std::string result;
    if (!hConnect) { return result; }

    const HINTERNET hRequest = WinHttpOpenRequest(
        hConnect,
        method.c_str(),
        path.c_str(),
        nullptr,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE
    );

    if (!hRequest) { return result; }

    // League's local API uses a self-signed cert; ignore validation errors
    DWORD flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                  SECURITY_FLAG_IGNORE_CERT_DATE_INVALID |
                  SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
    WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &flags, sizeof(flags));

    const bool ok = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        0,
        0
    ) && WinHttpReceiveResponse(hRequest, nullptr);

    if (!ok)
    {
        WinHttpCloseHandle(hRequest);
        return result;
    }

    result = GetBody(hRequest);

    WinHttpCloseHandle(hRequest);
    return result;
}
