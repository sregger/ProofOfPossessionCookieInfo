// Small utility to test the code
// Should only be used after calling `node-gyp rebuild`
// An exec can be created using
//   pkg proof.js --t node16-win-x64
const os = require('os');

if (os.type() === 'Windows_NT') {
    const cookieInfoManager = require('./build/Release/cookie-info-manager.node')
    const urls = [
        "https://login.microsoftonline.com/2a789914-be8c-49c8-9f76-a78c776ba89d/login"
    ]

    for (var url of urls) {
        const value = cookieInfoManager.getCookieInfoForUri("https://login.microsoftonline.com/2a789914-be8c-49c8-9f76-a78c776ba89d/saml2")
        console.log(`cookieInfoManager.getCookieInfoForUri("${url}") : ${JSON.stringify(value, undefined, 2)}\n`)
    }
}