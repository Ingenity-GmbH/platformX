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

# windows
cc_library(
    name = "windows_headers",
    deps = [
        "//include:headers"
    ],
    hdrs = glob(["windows/*.h"]),
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "platformX",
    deps = [
        ":windows_headers"
    ],
    srcs = glob(["*.cpp", "windows/*.cpp"]),
    linkshared = True,
    copts = [
        "/std:c++17",
        "/utf-8",
        "/DBUILDING_DLL",
        "/DUNICODE"
    ],
    linkopts = [
        "-DEFAULTLIB:user32",
        "-DEFAULTLIB:gdi32",
        "-DEFAULTLIB:UxTheme"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "linux_ui",
    srcs = ["linux/linux_ui.cpp"],
    hdrs = [
        "linux/linux_ui.h",
    ],
    deps = [
        "//include:headers"
    ],
    copts = [
        "-std=c++17",
    ],
    linkopts = [
        "-lX11",
        "-lXext",
    ],
    visibility = ["//visibility:public"],
)
