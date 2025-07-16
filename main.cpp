#include "include/application.h"

/* controls */
PXApplicationUniquePtr app;
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
PXTreeViewSharedPtr treeview;
PXStatusBarSharedPtr statusbar;

/* callbacks */
void button1click() {
    combobox->addNode(PXNode(edit->getTitle()));
    checkbox->toggleState();
    radioButton->toggleState();
    
    listbox->addNode(PXNode("main:"));
    for (const auto control : mainWnd->getControls()) {
        listbox->addNode(PXNode(control->getTitle()));
        listbox->addNode(PXNode("   " + control->getParent()->getTitle()));
    }
    listbox->addNode(PXNode("child:"));
    for (const auto control : childWnd->getControls()) {
        listbox->addNode(PXNode(control->getTitle()));
        listbox->addNode(PXNode("   " + control->getParent()->getTitle()));
    }
    listbox->addNode(PXNode("group:"));
    for (const auto control : groupbox->getControls()) {
        listbox->addNode(PXNode(control->getTitle()));
        listbox->addNode(PXNode("   " + control->getParent()->getTitle()));
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

void treeviewClick() {
    edit->setTitle(treeview->getSelectedNode()->title);
}

int main() {
    app = createApplication();
    
    mainWnd = createMainWindow("platformX App");
    childWnd = createWindow("child win", mainWnd);
    
    btn2 = createButton("btn2", mainWnd, PXPosition(100,10), button2click);
    edit = createEdit("edit", mainWnd, PXPosition(10,60), editClick);
    text = createText("Hello PlatformX", mainWnd, PXPosition(10,110));
    treeview = createTreeView("tree view", mainWnd, PXPosition(10, 450), treeviewClick);
    combobox = createComboBox("combobox", mainWnd, PXPosition(10,230));
    progress = createProgressBar("progressbar", mainWnd, PXPosition(10, 300));
    progress->configure(0,100,1);
    progress->setPos(25);
    progress->setColor(PXColor(0x80,0xC8,0xB0), PXColor(0xF0,0xF0,0xF0));
    
    btn = createButton("btn child", childWnd, PXPosition(10,10), button1click);
    listbox = createListBox("listbox", childWnd, PXPosition(10,160), PXSize(300,400));
    groupbox = createGroupBox("group", childWnd, PXPosition(10,50));
    checkbox = createCheckBox("option", groupbox, PXPosition(10,50));
    radioButton = createRadioButton("radio", groupbox, PXPosition(10,80));
    statusbar = createStatusBar("statusbar", mainWnd);
    statusbar->addPart(0.2, "status");
    statusbar->addPart(0.8, "time");
    statusbar->addPart(0.5, "p2");

    PXNode blubb1("blubb1");
    PXNode blubb2("blubb2");
    PXNode blubb3("blubb3");
    treeview->addNode(blubb1);
    treeview->addNode(blubb2);
    treeview->addNode(blubb3);
    treeview->addNode(PXNode("blubb11", &blubb1));
    treeview->addNode(PXNode("blubb12", &blubb1));
    treeview->addNode(PXNode("blubb31", &blubb3));
    

    return app->runEventLoop();
}
