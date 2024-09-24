#include "include/application.h"

/* controls */
PXWindow* wnd;
PXButton* btn;
PXButton* btn2;
PXEdit* edit;
PXText* text;
PXListBox* listbox;

/* callbacks */
void button1click() {
    listbox->addItem(edit->getTitle(), 5);
}

void button2click() {
    listbox->removeItem(listbox->getSelectedItem());
}

void editClick(const uint32_t& key) {
    printf("%x clicked\n", key);
}


int main() {
    wnd = createWindow("platformX App");
    std::unique_ptr<PXApplication> app(createApplication(wnd));

    btn = createButton("testbtn", app->getMainWindow(), PXPosition(10,10), button1click);
    btn2 = createButton("testbtn", app->getMainWindow(), PXPosition(100,10), button2click);
    edit = createEdit("", app->getMainWindow(), PXPosition(10,60), editClick);
    text = createText("Hello PlatformX", app->getMainWindow(), PXPosition(10,110));
    listbox = createListBox("Hello PlatformX", app->getMainWindow(), PXPosition(10,160));

    app->runEventLoop();

    return EXIT_SUCCESS;
}
