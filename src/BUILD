# windows
cc_library(
    name = "windows_headers",
    deps = [
        "//include:headers",
    ],
    hdrs = glob(["windows/*.h"]),
)

cc_binary(
    name = "platformX.dll",
    deps = [
        ":windows_headers",
    ],
    srcs = glob(["*.cpp", "windows/*.cpp"]),
    linkshared = True,
    copts = [
        "/std:c++17",
        "/utf-8",
        "/DBUILDING_DLL",
        "/DUNICODE",
    ],
    linkopts = [
        "-DEFAULTLIB:user32",
        "-DEFAULTLIB:gdi32",
        "-DEFAULTLIB:UxTheme",
    ],
)

# linux
cc_library(
    name = "linux_headers",
    deps = [
        "//include:headers",
    ],
    hdrs = glob(["linux/*.h"]),
)

cc_binary(
    name = "platformX.so",
    deps = [
        ":linux_headers",
    ],
    srcs = glob(["*.cpp", "linux/*.cpp"]),
    linkshared = True,
    copts = [
        "-std=c++17",
    ],
    linkopts = [
        "-lX11",
        "-lXext",
    ],
)

# macos
objc_library(
    name = "macos_sources",
    deps = [
        "//include:headers",
    ],
    hdrs = glob(["macos/*.h", "macos/*.hh"]),
    srcs = glob(["macos/*.mm"]),
    copts = [
        "-fno-objc-arc",
    ],
)

cc_binary(
    name = "platformX.dylib",
    deps = [
        ":macos_sources",
    ],
    srcs = glob(["*.cpp", "macos/*.cpp"]),
    linkshared = True,
    copts = [
        "-std=c++17",
        "-xobjective-c++",
    ],
    linkopts = [
        "-framework AppKit",
    ],
)
