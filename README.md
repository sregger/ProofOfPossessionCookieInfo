## Description

Exposes the [ProofOfPossessionCookieInfo.h](https://learn.microsoft.com/en-us/windows/win32/api/proofofpossessioncookieinfo/) functionality to JavaScript via [N-API](https://nodejs.org/api/n-api.html).

Support for Azure Conditional Access

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