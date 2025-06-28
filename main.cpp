#include "include/application.h"

/* controls */
PXApplUniquePtr app;
PXWindowSharedPtr mainWnd;
PXWindowSharedPtr childWnd;
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
    util::setWindowState(childWnd->getHandle(), SW_NORMAL);
}

void editClick(const uint32_t& key) {
    progress->incStep();
}

int main() {
    mainWnd = SHARED(PXWindow, createMainWindow("platformX App"));
    app = UNIQUE(PXApplication, createApplication(mainWnd));
    
    childWnd = SHARED(PXWindow, createWindow("child win", mainWnd->getSharedPtr()));
    btn = createButton("btn child", childWnd->getSharedPtr(), PXPosition(10,10), button1click);
    listbox = createListBox("", mainWnd->getSharedPtr(), PXPosition(10,160));
    btn2 = createButton("btn2", mainWnd->getSharedPtr(), PXPosition(100,10), button2click);
    edit = createEdit("", mainWnd->getSharedPtr(), PXPosition(10,60), editClick);
    text = createText("Hello PlatformX", mainWnd->getSharedPtr(), PXPosition(10,110));
    combobox = createComboBox("", mainWnd->getSharedPtr(), PXPosition(10,230));
    progress = createProgressBar("", mainWnd->getSharedPtr(), PXPosition(10, 300));
    progress->configure(0,100,1);
    progress->setPos(25);
    progress->setColor(PXColor(0x80,0xC8,0xB0), PXColor(0xF0,0xF0,0xF0));

    app->runEventLoop();


    return EXIT_SUCCESS;
}
