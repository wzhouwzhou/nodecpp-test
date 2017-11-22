{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "src/export/hello.cc" ]
    },
    {
        "include_dirs": [
          "src/headers"
        ],
      "target_name": "math",
      "sources": [ "src/export/math.cc", "src/deps/math_deps.cxx", "src/headers/math_deps.h" ]
    },
    {
        "include_dirs": [
          "src/headers"
        ],
      "target_name": "arrays",
      "sources": [ "src/export/arrays.cc", "src/deps/array_deps.cxx" ]
    }
  ]
}
