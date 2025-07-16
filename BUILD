# debug config
config_setting(
    name = "debug_build",
    values = {"compilation_mode": "dbg"},
)

# example app related to current OS
cc_binary(
    name = "native_ui_app",
    srcs = ["main.cpp"],
    deps = select({
        "@bazel_tools//src/conditions:darwin": [":macos_ui"],
        "@bazel_tools//src/conditions:windows": [
            ":windows_ui", 
        ],
        "//conditions:default": [":linux_ui"],
    }),
)

# macos
cc_library(
    name = "macos_ui",
    deps = [
        "//third-party:metal-cpp",
        "//include:headers",
        "//src:macos_ui",
    ],
    copts = [
        "-Wall",
        "-std=c++17",
    ],
    linkopts = [
        "-framework Metal",
        "-framework Foundation",
        "-framework Cocoa",
        "-framework CoreGraphics",
    ],
)

# windows
cc_import(
    name = "platformX",
    interface_library = select({
        ":debug_build":         "bazel-out/x64_windows-dbg/bin/src/platformX.if.lib",
        "//conditions:default": "bazel-out/x64_windows-fastbuild/bin/src/platformX.if.lib",
    }),
    shared_library = select({
        ":debug_build":         "bazel-out/x64_windows-dbg/bin/src/platformX.dll",
        "//conditions:default": "bazel-out/x64_windows-fastbuild/bin/src/platformX.dll",
    })
)

cc_library(
    name = "windows_ui",
    deps = [
        "//include:headers",
        ":platformX"
    ],
    copts = [
        "/Wall",
        "/std:c++17",
    ]
)

# linux
cc_library(
    name = "linux_ui",
    deps = [
        "//include:headers",
        "//src:linux_ui",
    ],
    copts = [
        "-Wall",
        "-std=c++17",
    ],
)
