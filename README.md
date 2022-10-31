## Description

Microsoft Azure AD Identity Provider (IDP) is popular with Enterprise Customers where it is leveraged by their Single Sign-On (SSO) solutions. A feature of Azure IDP is [Conditional Access](https://learn.microsoft.com/en-us/defender-cloud-apps/proxy-deployment-aad) which can be used to ensure only enrolled, or domain specific, devices are used. Typically this aspect of the IDP flow is powered by [WebView2](https://developer.microsoft.com/en-us/microsoft-edge/webview2/), which is problematic for Electron users.

This module overcomes that limit. It exposes the native `GetCookieInfoForUri(..)` function from the [ProofOfPossessionCookieInfo.h](https://learn.microsoft.com/en-us/windows/win32/api/proofofpossessioncookieinfo/) header to JavaScript via [N-API](https://nodejs.org/api/n-api.html). This function returns a token which can be used to authenticate when connecting to `login.microsoftonline.com` as part of the Azure IDP flow. e.g.

    x-ms-RefreshTokenCredential: eyJhbGciOiJIUzI1NiIsICJrZGZfdmVyIjoyLCAiY3R4IjoiRTA2RnZWbm9mU2RSNFpvSHNxWjlIOWsyeVdTTGVETHAifQ

The data accessed via `GetCookieInfoForUri(..)` is in the following format

    x-ms-RefreshTokenCredential eyJhbGciOiJIUzI1NiIsICJrZGZfdmVyIjoyLCAiY3R4IjoiRTA2RnZWbm9mU2RSNFpvSHNxWjlIOWsyeVdTTGVETHAifQ; path=/; domain=login.microsoftonline.com; secure; httponly"

of which this module returns

    [
      {
        name: "x-ms-RefreshTokenCredential",
        data: "eyJhbGciOiJIUzI1NiIsICJrZGZfdmVyIjoyLCAiY3R4IjoiRTA2RnZWbm9mU2RSNFpvSHNxWjlIOWsyeVdTTGVETHAifQ"
      }
    ]

This function is Windows specific but the module includes a "do nothing" implementation on other platforms. For Windows machines, which are not enrolled for conditional access, and non-Windows platforms this module returns an empty list.

## Build Requirements

* NodeJS 16
* Python 3
* Visual Studio
* ATL libraries for altbase.h

## How to build

### C++ code

Install `node-gyp` globally with

> npm install node-gyp --global

This package will allow you to build native code and package it for JavaScript consumption. To build the C++ code use

> node-gyp rebuild

The output of which is a `build\Release\cookie-info-manager.node` file which can be `required(..)` in NodeJS. e.g.

    const cookieInfoManager = require('bindings')('cookie-info-manager');

Note: You can use 

    const cookieInfoManager = require('./build/Release/cookie-info-manager.node')

but it's a good practice to use `bindings` instead.

### Usage in NodeJS

TODO

### Executable

An executable is not required. But it can be useful for standalone testing. Based on these [instructions](https://medium.com/jspoint/how-to-create-an-executable-exe-file-from-javascript-code-using-node-js-45154ba4de20) install `pkg` globally with

> npm install pkg --global

then create a Windows `.exe` with

> pkg index.js --t node16-win-x64

which will create an `index.exe` file. 

## Resources

* [A simple guide to load C/C++ code into Node.js JavaScript Applications](https://medium.com/jspoint/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32)
* [GetCookieInfoForUri](https://learn.microsoft.com/en-us/windows/win32/api/proofofpossessioncookieinfo/nf-proofofpossessioncookieinfo-iproofofpossessioncookieinfomanager-getcookieinfoforuri)