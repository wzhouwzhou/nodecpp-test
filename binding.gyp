{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "hello",
      "sources": [ "src/export/hello.cc" ]
    },
    {
        "include_dirs": [
          "src/headers"
        ],
      "target_name": "math",
      "sources": [ "src/export/math.cc", "src/deps/math_deps.cxx", "src/headers/math_deps.h" ]
    }
  ]
}
