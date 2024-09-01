cc_binary(
    name = "native_ui_app",
    srcs = ["main.cpp"],
    deps = select({
        "@bazel_tools//src/conditions:darwin": [":macos_ui"],
        "@bazel_tools//src/conditions:windows": [":windows_ui"],
        "//conditions:default": [":linux_ui"],
    }),
)

cc_library(
    name = "macos_ui",
    copts = [
        "-Wall",
        "-std=c++17",
    ],
    linkopts = [
        "-framework Metal",
        "-framework Foundation",
        "-framework Cocoa",
    ],
    deps = [
        "//third-party:metal-cpp",
        "//include:headers",
        "//src:macos_ui",
    ],
)

cc_library(
    name = "windows_ui",
    deps = [
        "//include:headers",
        "//src:windows_ui",
    ],
    copts = [
        "-Wall",
        "-std=c++17",
    ],
)

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
