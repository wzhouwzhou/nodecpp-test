{
    "targets": [
        {
            "target_name": "hello",
            "sources": [ "src/export/hello.cc" ],
            "defines": [
                'DEBUG="<!(echo $DEBUG)"'
            ]
        },
        {
            "include_dirs": [
                "src/headers"
            ],
            "target_name": "math",
            "sources": [
                "src/export/math.cc",
                "src/deps/math_deps.cxx",
                "src/headers/math_deps.h",
                "src/headers/timings.hpp"
            ],
            "defines": [
                'DEBUG="<!(echo $DEBUG)"'
            ]
        },
        {
            "include_dirs": [
                "src/headers"
            ],
            "target_name": "arrays",
            "sources": [
                "src/export/arrays.cc",
                "src/deps/array_deps.cxx",
                "src/proto_objects/ArrayUtil.cpp",
                "src/headers/arrays.h",
                "src/headers/arrayutil.hpp"
            ],
            "defines": [
                'DEBUG="<!(echo $DEBUG)"'
            ]
        }
    ]
}
