package(default_visibility = ["//visibility:public"])

cc_library(
    name = "macos_ui",
    srcs = ["macos/application.cpp",
    ],
    hdrs = [
        "//include:global.h",
        "//include:application.h",
        "//include:control.h",
        "//include:controls.h",
        "macos/application.h",
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
    srcs = [
        "windows/application.cpp",
        "windows/window.cpp",
        "windows/controls.cpp",
        "windows/util.cpp",
    ],
    hdrs = [
        "//include:global.h",
        "//include:application.h",
        "//include:control.h",
        "//include:controls.h",
        "windows/application.h",
        "windows/window.h",
        "windows/controls.h",
        "windows/util.h",
    ],
    copts = [
        "/std:c++17",
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
    hdrs = [
        "//include:global.h",
        "//include:application.h",
        "//include:control.h",
        "//include:controls.h",
        "linux/linux_ui.h",
    ],
    copts = [
        "-std=c++17",
    ],
    linkopts = [
        "-lX11",
        "lXext",
    ],
    visibility = ["//visibility:public"],
)
