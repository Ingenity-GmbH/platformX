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
PXCheckBoxSharedPtr checkbox;
PXRadioButtonSharedPtr radioButton;
PXGroupBoxSharedPtr groupbox;

/* callbacks */
void button1click() {
    combobox->addItem(edit->getTitle(), 5);
    checkbox->toggleState();
    radioButton->toggleState();
    
    listbox->addItem("main:");;
    for (const auto control : mainWnd->getControls()) {
        listbox->addItem(control->getTitle());
        listbox->addItem("   " + (control->getParent() ? control->getParent()->getTitle() : "none"));
    }
    listbox->addItem("child:");
    for (const auto control : childWnd->getControls()) {
        listbox->addItem(control->getTitle());
        listbox->addItem("   " + (control->getParent() ? control->getParent()->getTitle() : "none"));
    }
    listbox->addItem("group:");
    for (const auto control : groupbox->getControls()) {
        listbox->addItem(control->getTitle());
        listbox->addItem("   " + (control->getParent() ? control->getParent()->getTitle() : "none"));
    }
}

void button2click() {
    util::setWindowState(childWnd->getHandle(), SW_NORMAL);
    checkbox->setState(true);
    radioButton->setState(true);
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
    edit = SHARED(PXEdit, createEdit("edit", mainWnd, PXPosition(10,60), editClick));
    text = SHARED(PXText, createText("Hello PlatformX", mainWnd, PXPosition(10,110)));
    listbox = SHARED(PXListBox, createListBox("listbox", childWnd, PXPosition(10,160), PXSize(300,400)));
    combobox = SHARED(PXComboBox, createComboBox("combobox", mainWnd, PXPosition(10,230)));
    progress = SHARED(PXProgressBar, createProgressBar("progressbar", mainWnd, PXPosition(10, 300)));
    progress->configure(0,100,1);
    progress->setPos(25);
    progress->setColor(PXColor(0x80,0xC8,0xB0), PXColor(0xF0,0xF0,0xF0));
    groupbox = SHARED(PXGroupBox, createGroupBox("group", childWnd, PXPosition(10,50)));
    checkbox = SHARED(PXCheckBox, createCheckBox("option", groupbox, PXPosition(10,50)));
    radioButton = SHARED(PXRadioButton, createRadioButton("radio", groupbox, PXPosition(10,80)));

    app->runEventLoop();


    return EXIT_SUCCESS;
}
