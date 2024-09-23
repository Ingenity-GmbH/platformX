#include "include/application.h"

PXApplication* app;
PXButton* btn;
PXButton* btn2;
PXEdit* edit;
PXText* text;

void button1click() {
    text->setTitle(edit->getTitle());
}
void button2click() {
    printf("title: %s\n", btn2->getTitle());
}

void editClick(const uint32_t& key) {
    printf("%x clicked\n", key);
}

int main() {
    app = createApplication("platformX App");
    btn = createButton("testbtn", app->getMainWindow(), PXPosition(10,10), button1click);
    btn2 = createButton("testbtn", app->getMainWindow(), PXPosition(100,10), button2click);
    edit = createEdit("", app->getMainWindow(), PXPosition(10,60), editClick);
    text = createText("Hello PlatformX", app->getMainWindow(), PXPosition(10,110));
    app->runEventLoop();

    delete app, btn, btn2, edit, text;

    return EXIT_SUCCESS;
}
