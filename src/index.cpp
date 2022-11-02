#include <napi.h>
#include <string>
#include <vector>
#include "cookie-info-manager.h"

Napi::Array getCookieInfo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string url = (std::string) info[0].ToString();

    // Call ProofOfPossessionCookieInfoManager to get the PRT
    std::vector<CookieInfo> cookies;
    bool success = getCookieInfoForUri(url, cookies);

    Napi::Array array = Napi::Array::New(info.Env(), cookies.size());

    // When using an `int` and building an electron installer it produced an error
    // error C2666: 'Napi::Object::operator []': 3 overloads have similar conversions
    // Switching to `uint32_t` as a workaround.
    uint32_t i = 0;
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
