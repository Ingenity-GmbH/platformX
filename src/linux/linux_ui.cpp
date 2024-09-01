#include <X11/Xlib.h>
#include "ui_interface.h"

class LinuxUI : public UIInterface {
    Display* display;
    Window window;
public:
    void createWindow() override {
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

    void showMessage(const char* message) override {
        // In a real application, you'd create a dialog window here
        // For simplicity, we'll just print to console
        printf("Message: %s\n", message);
    }

    void runEventLoop() override {
        XEvent event;
        while (true) {
            XNextEvent(display, &event);
            // Handle events here
        }
    }
};

UIInterface* createNativeUI() {
    return new LinuxUI();
}
