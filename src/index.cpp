#include <napi.h>
#include <string>
#include "cookie-info-manager.h"

Napi::Array getCookieInfo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string url = (std::string) info[0].ToString();

    // Call ProofOfPossessionCookieInfoManager to get the PRT
    std::vector<CookieInfo> cookies;
    bool success = getCookieInfoForUri(url, cookies);

    Napi::Array array = Napi::Array::New(info.Env(), cookies.size());

    int i = 0;
    for (const auto cookie : cookies) {
        Napi::Object object = Napi::Object::New( env );
        object.Set("name", Napi::String::New( env, cookie.name ));
        object.Set("data", Napi::String::New( env, cookie.data ));

        array[i] = object;
        i++;
    }

    return array;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "getCookieInfoForUri"),
        Napi::Function::New(env, getCookieInfo)
    );

    return exports;
}

NODE_API_MODULE(greet, Init)
