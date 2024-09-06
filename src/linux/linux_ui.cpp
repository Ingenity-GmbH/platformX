#include "linux_ui.h"

#include "include/global.h"

#pragma region LinuxUI
void LinuxUI::createWindow() {
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        return;
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                    10, 10, 300, 200, 1,
                                    BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
}

void LinuxUI::runEventLoop() {
    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        // Handle events here
    }
}

UIInterface* createUI() {
    return new LinuxUI();
}
#pragma endregion LinuxUI
