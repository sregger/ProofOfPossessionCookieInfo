#include <napi.h>
#include <string>
#include "cookie-info-manager.h"

Napi::String getCookieInfo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string user = (std::string) info[0].ToString();
    std::string result = getCookieInfoForUri(user);

    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "getCookieInfoForUri"),
        Napi::Function::New(env, getCookieInfo)
    );

    return exports;
}

NODE_API_MODULE(greet, Init)
