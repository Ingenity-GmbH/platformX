cc_library(
    name = "macos_ui",
    srcs = ["macos/macos_ui.cpp"],
    hdrs = [
        "macos/macos_ui.h",
        "//include:global.h",
        "//include:ui_interface.h",
    ],
    copts = [
        "-std=c++17",
        "-I./third-party/metal-cpp",
        "-fno-objc-arc",
    ],
    deps = [
        "//third-party:metal-cpp",
    ],
    linkopts = [
        "-framework Metal",
        "-framework Foundation",
        "-framework Cocoa",
        "-framework CoreGraphics",
    ],
    defines = [
        "NS_PRIVATE_IMPLEMENTATION",
        "MTL_PRIVATE_IMPLEMENTATION",
        "MTK_PRIVATE_IMPLEMENTATION",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "windows_ui",
    srcs = ["windows/windows_ui.cpp"],
    hdrs = [
        "windows/windows_ui.h",
        "//include:global.h",
        "//include:ui_interface.h"
    ],
    linkopts = [
        "-DEFAULTLIB:user32",
        "-DEFAULTLIB:gdi32",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "linux_ui",
    srcs = ["linux/linux_ui.cpp"],
    hdrs = ["//include:ui_interface.h"],
    linkopts = [
        "-lX11",
        "lXext",
    ],
    visibility = ["//visibility:public"],
)
