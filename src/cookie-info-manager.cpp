#include <windows.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <ProofOfPossessionCookieInfo.h>
#include <stringapiset.h>
#include <atlbase.h>
#include "cookie-info-manager.h"

using namespace std;

struct CookieInfo {
    std::string name;
    std::string data;
    std::string flags;
    std::string p3pHeader;
};

std::wstring toWString(const std::string& input)
{
    // Convert UTF-8 to UTF-16
    if (!input.empty())
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &input[0], static_cast<int>(input.length()), nullptr, 0);
        std::wstring utf16String(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &input[0], static_cast<int>(input.length()), &utf16String[0], size_needed);
        return utf16String;
    }

    return std::wstring();
}

bool isSpace(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
            return true;
        default:
            return false;
    }
}

std::vector<std::string> split(const std::string& input, const int subLength)
{
    std::vector<std::string> result;
    if (input.empty())
    {
        return result;
    }
    auto subStrCount = input.length()/subLength;
    for (auto i = 0; i < subStrCount; i++)
    {
        result.push_back(input.substr(i * subLength, subLength));
    }
    if (input.length() % subLength != 0)
    {
        result.push_back(input.substr(subLength * subStrCount));
    }
    return result;
}

std::string getCookieInfoForUri( std::string uri ) {
    cout << "Called getCookieInfoForUri" << endl;

    CoInitialize(nullptr);

    cout << "Called CoInitialize(nullptr)" << endl;


    std::string deviceId = "Nothing";
    std::vector<CookieInfo> cookies = {};

    DWORD cookieInfoCount = 0;
    DWORD* cookieInfoCountPtr = &cookieInfoCount;

    ProofOfPossessionCookieInfo cookieInfo = {};
    ProofOfPossessionCookieInfo* cookieInfoPtr = &cookieInfo;
    ProofOfPossessionCookieInfo** cookieInfoPtrPtr = &cookieInfoPtr;

    IProofOfPossessionCookieInfoManager* cookieInfoManager = NULL;
    HRESULT hResult = CoCreateInstance(__uuidof(ProofOfPossessionCookieInfoManager), NULL, CLSCTX_INPROC_SERVER, __uuidof(IProofOfPossessionCookieInfoManager), (void**)&cookieInfoManager);

    cout << "HRESULT " << hResult << endl;

    if (SUCCEEDED(hResult))
    {
        HRESULT cookieInfoResult = cookieInfoManager->GetCookieInfoForUri(toWString(uri).c_str(), cookieInfoCountPtr, cookieInfoPtrPtr);
        cout << "SUCCEEDED(hResult) cookieInfoResult " << cookieInfoResult << endl;

        if (SUCCEEDED(cookieInfoResult) && cookieInfoPtrPtr && *cookieInfoPtrPtr)
        {
            cout << "SUCCEEDED(cookieInfoResult) with count " << cookieInfoCount << endl;
            for (DWORD i = 0; i < cookieInfoCount; i++)
            {
                if (cookieInfoPtr[i].name && cookieInfoPtr[i].data)
                {
                    CookieInfo cookie;
                    cookie.name = CW2A(cookieInfoPtr[i].name);
                    cookie.data = CW2A(cookieInfoPtr[i].data);

                    deviceId = cookie.name + " - " + cookie.data;

                    // Splitting the data fetched by ;
                    // The data we receive is formatted as "<PRT string>; path=/; domain=login.microsoftonline.com; secure; httponly"
                    const auto splitData = split(cookie.data, ';');
                    cookie.data = splitData.size() > 1 ? splitData[0] : cookie.data;

                    if (!cookie.data.empty())
                    {
                        cookies.push_back(cookie);
                    }
                }
            }
        }

        cookieInfoManager->Release();
    }

    CoUninitialize();

    return deviceId;
}