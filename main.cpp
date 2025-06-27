#include "include/application.h"
#include <WinUser.h>

/* controls */
PXWindow* wnd;
PXWindow* childWnd;
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
    printf("b1 clicked\n");
}

void button2click() {
    progress->incStep();
    util::setWindowState(childWnd->getHandle(), SW_NORMAL);
    printf("b2 clicked\n");

}

void editClick(const uint32_t& key) {
    printf("%x edit clicked\n", key);
}


int main() {
    wnd = createMainWindow("platformX App");
    std::unique_ptr<PXApplication> app(createApplication(wnd));
    
    
    childWnd = createWindow("child", app->getMainWindow());
    btn = createButton("testbtn", app->getMainWindow(), PXPosition(10,10), button1click);
    listbox = createListBox("", app->getMainWindow(), PXPosition(10,160));
    btn2 = createButton("testbtn", app->getMainWindow(), PXPosition(100,10), button2click);
    edit = createEdit("", app->getMainWindow(), PXPosition(10,60), editClick);
    text = createText("Hello PlatformX", app->getMainWindow(), PXPosition(10,110));
    combobox = createComboBox("", app->getMainWindow(), PXPosition(10,230));
    progress = createProgressBar("", app->getMainWindow(), PXPosition(10, 300));
    progress->configure(0,100,1);
    progress->setPos(25);
    progress->setColor(PXColor(0x80,0xC8,0xB0), PXColor(0xF0,0xF0,0xF0));

    app->runEventLoop();

    return EXIT_SUCCESS;
}
