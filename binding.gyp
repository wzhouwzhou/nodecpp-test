{
    "targets": [
        {
            "include_dirs": [
                "src/headers",
                "lib/curlpp-0.8.1/include"
            ],
            "target_name": "curlpp",
            "sources": [
                "src/export/curlpp.cc",
            ],
            "defines": [
                'DEBUG="<!(echo $DEBUG)"'
            ],
            'cflags': ['-fPIC', '-lcurl'],
            'cflags_cc!': ['-fno-rtti', '-O3'],
            'conditions': [
                ['OS=="mac"', {
                    'libraries': [
                        '../lib/curlpp-0.8.1/build/libcurlpp.a',
                         '<!@(node "<(module_root_dir)/tools/curl-config.js" --libs)'
                    ],
                    'variables': {
                        'osx_min_version': "<!(sw_vers -productVersion | awk -F \'.\' \'{print $1 \".\" $2}\')"
                    },
                    "xcode_settings": {
                        'MACOSX_DEPLOYMENT_TARGET': '<(osx_min_version)',
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        'GCC_ENABLE_CPP_RTTI': 'YES',
                        'OTHER_CFLAGS': [
                            '-arch x86_64 -O2 -g -flto -mmacosx-version-min=<(osx_min_version) -fPIC',
                            '<!@(node "<(module_root_dir)/tools/curl-config.js" --cflags)'
                        ],
                        'OTHER_LDFLAGS': ['-arch x86_64 -mmacosx-version-min=<(osx_min_version) -flto'],
                        'OTHER_CPLUSPLUSFLAGS':[
                            '-std=c++11','-stdlib=libc++',
                            '<!@(node "<(module_root_dir)/tools/curl-config.js" --cflags)',
                        ]
                    }
                }],
                ['OS=="win"', {
                    'libraries': [
                        '../lib/curlpp-0.8.1/build/libcurlpp.lib'
                    ],
                    'msvs_settings': { # https://github.com/JCMais/node-libcurl/blob/develop/binding.gyp
                        'VCCLCompilerTool': {
                            'DisableSpecificWarnings': ['4506', '4838'] #warning about v8 inline function and narrowing
                        }
                    },
                    'configurations' : {
                        'Release': {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    'ExceptionHandling': '1',
                                    'Optimization': 2,                  # /O2 safe optimization
                                    'FavorSizeOrSpeed': 1,              # /Ot, favour speed over size
                                    'InlineFunctionExpansion': 2,       # /Ob2, inline anything eligible
                                    'WholeProgramOptimization': 'true', # /GL, whole program optimization, needed for LTCG
                                    'OmitFramePointers': 'true',
                                    'EnableFunctionLevelLinking': 'true',
                                    'EnableIntrinsicFunctions': 'true',
                                    'WarnAsError': 'true'
                                }
                            }
                        },
                        'Debug': {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    'WarnAsError': 'false'
                                }
                            }
                        }
                    },
                    'dependencies': [
                        '<!@(node "<(module_root_dir)/tools/retrieve-win-deps.js")'
                    ],
                }],
                ['OS=="linux"', {
                    'libraries': [
                        '../lib/curlpp-0.8.1/build/libcurlpp.a'
                    ]
                }]
            ]
        },
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
