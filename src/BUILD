# windows
cc_library(
    name = "windows_headers",
    deps = [
        "//include:headers"
    ],
    hdrs = glob(["windows/*.h"])
)

cc_binary(
    name = "platformX.dll",
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
    ]
)

# linux
cc_library(
    name = "linux_headers",
    deps = [
        "//include:headers"
    ],
    hdrs = glob(["linux/*.h"])
)

cc_binary(
    name = "platformX.so",
    deps = [
        ":linux_headers"
    ],
    srcs = glob(["*.cpp", "linux/*.cpp"]),
    linkshared = True,
    copts = [
        "-std=c++17",
    ],
    linkopts = [
        "-lX11",
        "-lXext",
    ]
)

# macos
cc_library(
    name = "macos_headers",
    deps = [
        "//include:headers"
    ],
    hdrs = glob(["macos/*.h"]),
)

cc_binary(
    name = "platformX.dylib",
    deps = [
        ":macos_headers",
        "//third-party:metal-cpp",
    ],
    srcs = glob(["*.cpp", "macos/*.cpp"]),
    linkshared = True,
    copts = [
        "-std=c++17",
        "-I./third-party/metal-cpp",
        "-fno-objc-arc",
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
    ]
)
