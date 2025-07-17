#include "include/application.h"

/* controls */
PXApplicationUniquePtr app;

int main() {
    app = createApplication();
   
    return app->runEventLoop();
}
