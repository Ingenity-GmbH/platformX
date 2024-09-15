#include "include/global.h"
#include "include/application.h"
#include "include/components.h"

void button1click() {
    printf("button1 clicked");
}

int main() {
    std::unique_ptr<Application> app(createApplication("platformX App"));
    std::unique_ptr<Button> btn(createButton("testbtn", Position(10,10), app->getWindow(), button1click));
    app->runEventLoop();

    return EXIT_SUCCESS;
}
