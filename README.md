## Description

Microsoft Azure AD Identity Provider (IDP) is popular with Enterprise Customers where it is leveraged by their Single Sign-On (SSO) solutions. A feature of Azure IDP is [Conditional Access](https://learn.microsoft.com/en-us/defender-cloud-apps/proxy-deployment-aad) which can be used to ensure only enrolled, or domain specific, devices are being used. Typically this aspect of the IDP flow is powered by [WebView2](https://developer.microsoft.com/en-us/microsoft-edge/webview2/), which is problematic for Electron users.

This module overcomes this limit. It exposes the native `GetCookieInfoForUri(..)` function from the [ProofOfPossessionCookieInfo.h](https://learn.microsoft.com/en-us/windows/win32/api/proofofpossessioncookieinfo/) header to JavaScript via [N-API](https://nodejs.org/api/n-api.html). This API returns a `x-ms-RefreshTokenCredential` = `token` header which can be used when connecting to `login.microsoftonline.com` as part of the Azure IDP flow. i.e. It adds support for Azure Conditional Access.

This module is Windows specific but includes a "do nothing" implementation on other platforms.

## Requirements

* NodeJS 16
* Python 3
* windows-build-tools
* ATL libraries for altbase.h

## Resources

Based on https://medium.com/jspoint/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32

Calls https://learn.microsoft.com/en-us/windows/win32/api/proofofpossessioncookieinfo/nf-proofofpossessioncookieinfo-iproofofpossessioncookieinfomanager-getcookieinfoforuri

## How to build

### C++ code

> node-gyp rebuild

### Executable

> npm install pkg --global

> pkg index.js

https://medium.com/jspoint/how-to-create-an-executable-exe-file-from-javascript-code-using-node-js-45154ba4de20