#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <ProofOfPossessionCookieInfo.h>
#include <atlbase.h>
#include "cookie-info-manager.h"

using namespace std;

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

std::vector<std::string> splitPRT(const std::string& input)
{
    std::stringstream stream(input);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(stream, segment, ';'))
    {
       seglist.push_back(segment);
    }

    return seglist;
}

bool getCookieInfoForUri( std::string uri, OUT std::vector<CookieInfo>& cookies ) {
    CoInitialize(nullptr);

    DWORD cookieInfoCount = 0;
    DWORD* cookieInfoCountPtr = &cookieInfoCount;

    ProofOfPossessionCookieInfo cookieInfo = {};
    ProofOfPossessionCookieInfo* cookieInfoPtr = &cookieInfo;
    ProofOfPossessionCookieInfo** cookieInfoPtrPtr = &cookieInfoPtr;

    IProofOfPossessionCookieInfoManager* cookieInfoManager = NULL;
    HRESULT hResult = CoCreateInstance(__uuidof(ProofOfPossessionCookieInfoManager), NULL, CLSCTX_INPROC_SERVER, __uuidof(IProofOfPossessionCookieInfoManager), (void**)&cookieInfoManager);

    bool isSuccess = false;

    if (SUCCEEDED(hResult))
    {
        HRESULT cookieInfoResult = cookieInfoManager->GetCookieInfoForUri(toWString(uri).c_str(), cookieInfoCountPtr, cookieInfoPtrPtr);

        if (SUCCEEDED(cookieInfoResult) && cookieInfoPtrPtr && *cookieInfoPtrPtr)
        {
            for (DWORD i = 0; i < cookieInfoCount; i++)
            {
                if (cookieInfoPtr[i].name && cookieInfoPtr[i].data)
                {
                    CookieInfo cookie;
                    cookie.name = CW2A(cookieInfoPtr[i].name);
                    cookie.data = CW2A(cookieInfoPtr[i].data);

                    // Splitting the data fetched by ;
                    // The data we receive is formatted as "<PRT string>; path=/; domain=login.microsoftonline.com; secure; httponly"
                    const auto splitData = splitPRT(cookie.data);
                    cookie.data = splitData.size() > 1 ? splitData[0] : cookie.data;

                    if (!cookie.data.empty())
                    {
                        cookies.push_back(cookie);
                    }
                }
            }
        }

        if (cookies.size())
        {
            isSuccess = true;
        }

        cookieInfoManager->Release();
    }

    CoUninitialize();

    return isSuccess;
}