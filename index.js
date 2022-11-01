const os = require('os');

function notWindowsSoDoNothing(url) {
    return "";
}

if (os.type() === 'Windows_NT') {
    const cookieInfoManager = require('bindings')('cookie-info-manager');
    exports.getCookieInfoForUri = cookieInfoManager.getCookieInfoForUri;
}
else {
    exports.getCookieInfoForUri = notWindowsSoDoNothing;
}