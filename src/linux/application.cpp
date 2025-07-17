#include "application.h"

#pragma region LinuxApplication
int LinuxApplication::runEventLoop() {
    display = XOpenDisplay(nullptr);
    XEvent event;

    if (!display)
        return -1;

    int screen = DefaultScreen(display);
    mainWnd = XCreateSimpleWindow(display, RootWindow(display, screen),
                                    10, 10, 300, 200, 1,
                                    BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, mainWnd, ExposureMask | KeyPressMask);
    XMapWindow(display, mainWnd);

    while (true) {
        XNextEvent(display, &event);
    }

    return 0;
}

PXApplicationUniquePtr createApplication() {
    return std::unique_ptr<PXApplication>(new LinuxApplication());
}
#pragma endregion LinuxUI
