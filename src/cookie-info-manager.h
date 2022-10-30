#include <string>

// See https://github.com/tpn/winsdk-10/blob/master/Include/10.0.10240.0/um/ProofOfPossessionCookieInfo.h#L76
struct CookieInfo {
    std::string name;
    std::string data;
    std::string flags;
    std::string p3pHeader;
};

bool getCookieInfoForUri( std::string name, std::vector<CookieInfo>& cookies );