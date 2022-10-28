const greetModule = require('./build/Release/cookie-info-manager.node') 

console.log(`export ${greetModule}`)
console.log(`greetModule.greetHello() : ${greetModule.greetHello("John")}`)

const addon = require('bindings')('cookie-info-manager');
exports.hello = addon.greetHello;

console.log(`addon.getCookieInfoForUri("Tim") : ${addon.getCookieInfoForUri("Tim")}`)