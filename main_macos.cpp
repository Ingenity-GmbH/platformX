#include "include/application.h"

int main() {
    PXApplicationUniquePtr app = createApplication();

    PXWindowSharedPtr mainWnd = createMainWindow("platformX App");
    PXWindowSharedPtr childWnd = createWindow("child win", mainWnd);

    PXButtonSharedPtr button = createButton("Click Me", childWnd, PXPosition(50, 150), [childWnd](void* arg) {
        printf("arg:%p\n", arg);
        childWnd->setPosition(PXPosition(100, 200));
    });

    return app->runEventLoop();
}
