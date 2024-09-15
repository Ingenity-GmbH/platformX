#include "include/global.h"
#include "include/application.h"
#include "include/components.h"

void button1click() {
    printf("button1 clicked\n");
}
void button2click() {
    printf("button2 clicked\n");
}

int main() {
    std::unique_ptr<Application> app(createApplication("platformX App"));
    std::unique_ptr<Button> btn(createButton("testbtn", Position(10,10), app->getMainWindow(), button1click));
    std::unique_ptr<Button> btn2(createButton("testbtn", Position(100,10), app->getMainWindow(), button2click));
    app->runEventLoop();

    return EXIT_SUCCESS;
}
