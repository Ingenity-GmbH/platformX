#include "include/application.h"

/* controls */
PXApplUniquePtr app;
PXWindowSharedPtr mainWnd;
PXWindowSharedPtr childWnd;
PXButtonSharedPtr btn;
PXButtonSharedPtr btn2;
PXEditSharedPtr edit;
PXTextSharedPtr text;
PXListBoxSharedPtr listbox;
PXComboBoxSharedPtr combobox;
PXProgressBarSharedPtr progress;

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
    app = UNIQUE(PXApplication, createApplication());
    
    mainWnd = SHARED(PXWindow, createMainWindow("platformX App"));
    childWnd = SHARED(PXWindow, createWindow("child win", mainWnd));
    
    btn = SHARED(PXButton, createButton("btn child", childWnd, PXPosition(10,10), button1click));
    btn2 = SHARED(PXButton, createButton("btn2", mainWnd, PXPosition(100,10), button2click));
    edit = SHARED(PXEdit, createEdit("", mainWnd, PXPosition(10,60), editClick));
    text = SHARED(PXText, createText("Hello PlatformX", mainWnd, PXPosition(10,110)));
    listbox = SHARED(PXListBox, createListBox("", childWnd, PXPosition(10,160)));
    combobox = SHARED(PXComboBox, createComboBox("", mainWnd, PXPosition(10,230)));
    progress = SHARED(PXProgressBar, createProgressBar("", mainWnd, PXPosition(10, 300)));
    progress->configure(0,100,1);
    progress->setPos(25);
    progress->setColor(PXColor(0x80,0xC8,0xB0), PXColor(0xF0,0xF0,0xF0));

    app->runEventLoop();


    return EXIT_SUCCESS;
}
