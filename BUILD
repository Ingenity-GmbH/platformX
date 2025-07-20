# debug config
config_setting(
    name = "debug_build",
    values = {"compilation_mode": "dbg"},
)

# example app related to current OS
cc_binary(
    name = "native_ui_app",
    # srcs = ["main.cpp"],
    srcs = select({
        "@platforms//os:windows": ["main_windows.cpp"],
        "@platforms//os:linux":   ["main_linux.cpp"],
        "@platforms//os:macos":   ["main_macos.cpp"],
    }),
    deps = select({
        "@platforms//os:windows": [":windows_ui"],
        "@platforms//os:linux":   [":linux_ui"],
        "@platforms//os:macos":   [":macos_ui"],
    }),
    copts = select({
        "@platforms//os:macos":   [ "-xobjective-c++"],
        "//conditions:default":   [],
    }),
)

# windows
cc_import(
    name = "platformX.dll",
    interface_library = select({
        ":debug_build":         "bazel-out/x64_windows-dbg/bin/src/platformX.dll.if.lib",
        "//conditions:default": "bazel-out/x64_windows-fastbuild/bin/src/platformX.dll.if.lib",
    }),
    shared_library = select({
        ":debug_build":         "bazel-out/x64_windows-dbg/bin/src/platformX.dll",
        "//conditions:default": "bazel-out/x64_windows-fastbuild/bin/src/platformX.dll",
    }),
)

cc_library(
    name = "windows_ui",
    deps = [
        "//include:headers",
        ":platformX.dll"
    ],
    copts = [
        "/Wall",
        "/std:c++17",
    ],
)

# linux
cc_import(
    name = "platformX.so",
    interface_library = None,
    shared_library = select({
        ":debug_build":         "bazel-out/k8-dbg/bin/src/platformX.so",
        "//conditions:default": "bazel-out/k8-fastbuild/bin/src/platformX.so",
    }),
)

cc_library(
    name = "linux_ui",
    deps = [
        "//include:headers",
        "//:platformX.so",
    ],
    copts = [
        "-Wall",
        "-std=c++17",
    ],
)

# macos
cc_import(
    name = "platformX.dylib",
    interface_library = None,
    shared_library = select({
        ":debug_build":         "bazel-out/darwin_x86_64-dbg/bin/src/platformX.dylib",
        "//conditions:default": "bazel-out/darwin_x86_64-fastbuild/bin/src/platformX.dylib",
    }),
)

cc_library(
    name = "macos_ui",
    deps = [
        "//include:headers",
        ":platformX.dylib",
    ],
    copts = [
        "-Wall",
        "-std=c++17",
    ],
)
