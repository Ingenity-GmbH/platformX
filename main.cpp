#include "include/application.h"

void button1click() {
    printf("button1 clicked\n");
}
void button2click() {
    printf("button2 clicked\n");
}

int main() {
    std::unique_ptr<PXApplication> app(createApplication("platformX App"));
    std::unique_ptr<PXButton> btn(createButton("testbtn", PXPosition(10,10), app->getMainWindow(), button1click));
    std::unique_ptr<PXButton> btn2(createButton("testbtn", PXPosition(100,10), app->getMainWindow(), button2click));
    app->runEventLoop();

    return EXIT_SUCCESS;
}
