#include "include/application.h"

/* controls */
PXApplicationUniquePtr app;
PXWindowSharedPtr mainWnd;
PXWindowSharedPtr childWnd;

int main() {
    app = createApplication();

    mainWnd = createMainWindow("platformX App");
    childWnd = createWindow("child win", mainWnd);
   
    return app->runEventLoop();
}
