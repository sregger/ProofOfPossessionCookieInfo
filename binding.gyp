{
  "targets": [
    {
      "target_name": "cookie-info-manager",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/cookie-info-manager.cpp",
        "./src/index.cpp"
      ],
      # Prevent a build on non-windows platforms, see https://gyp.gsrc.io/docs/InputFormatReference.md#pattern-lists-example
      'conditions': [['OS!="win"', {'sources/': [['exclude', '.cpp$']]}]],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}