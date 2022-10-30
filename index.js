const os = require('os');
const greetModule = require('./build/Release/cookie-info-manager.node')

function notWindowsSoDoNothing(url) {
    return "";
}

if (os.type() === 'Windows_NT') {
    const cookieInfoManager = require('bindings')('cookie-info-manager');
    exports.getCookieInfoForUri = cookieInfoManager.getCookieInfoForUri;

    const urls = [
        "Upper Case",
        "lower case",
        "Tim",
        "tim",
        "https://www.google.com/",
        "login.microsoftonline.com",
        "https://login.microsoftonline.com/2a789914-be8c-49c8-9f76-a78c776ba89d/saml2",
        "https://login.microsoftonline.com/common/GetCredentialType?mkt=en-US",
        "https://login.microsoftonline.com/2a789914-be8c-49c8-9f76-a78c776ba89d/login"
    ]

    for (var url of urls) {
        const cookies = cookieInfoManager.getCookieInfoForUri("https://login.microsoftonline.com/2a789914-be8c-49c8-9f76-a78c776ba89d/saml2")
        for (const cookie of cookies) {
            console.log(`cookieInfoManager.getCookieInfoForUri("${url}") : ${cookie.name} - ${cookie.data}\n`)
        }
    }
}
else {
    exports.getCookieInfoForUri = notWindowsSoDoNothing;
}