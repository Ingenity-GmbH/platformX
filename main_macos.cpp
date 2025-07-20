#include "include/application.h"

/* controls */
PXApplicationUniquePtr app;
PXWindowSharedPtr mainWnd;
PXWindowSharedPtr childWnd;
PXButtonSharedPtr button;
 
void buttonClick() {
    printf("Button clicked!\n");
}

int main() {
    app = createApplication();

    mainWnd = createMainWindow("platformX App");
    childWnd = createWindow("child win", mainWnd);

    button = createButton("Click Me", childWnd, PXPosition(50, 150), buttonClick);

    return app->runEventLoop();
}
