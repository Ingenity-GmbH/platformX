#include "include/application.h"

/* controls */
PXWindow* wnd;
PXButton* btn;
PXButton* btn2;
PXEdit* edit;
PXText* text;
PXListBox* listbox;
PXComboBox* combobox;
PXProgressBar* progress;

/* callbacks */
void button1click() {
    listbox->addItem(edit->getTitle(), 5);
    combobox->addItem(edit->getTitle(), 5);
}

void button2click() {
    progress->incStep();
    edit->setTitle(btn2->getTitle());
    btn2->setTitle("Button2");
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
    listbox = createListBox("", app->getMainWindow(), PXPosition(10,160));
    combobox = createComboBox("", app->getMainWindow(), PXPosition(10,230));
    progress = createProgressBar("", app->getMainWindow(), PXPosition(10, 300));
    progress->configure(0,100,1);
    progress->setPos(25);
    progress->setColor(PXColor(0x80,0xC8,0xB0), PXColor(0xF0,0xF0,0xF0));

    app->runEventLoop();

    return EXIT_SUCCESS;
}
