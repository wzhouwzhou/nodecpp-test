{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "src/export/hello.cc" ]
    },
    {
      "target_name": "math",
      "sources": [ "src/export/math.cc", "src/deps/math_deps.cxx", "src/headers/math_deps.h" ]
    }
  ]
}
