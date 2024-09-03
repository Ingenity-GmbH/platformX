#include <memory>
#include "include/ui_interface.h"

int main() {
    std::unique_ptr<UIInterface> ui(createNativeUI());
    ui->createWindow("window title");
    ui->showMessage("Hello, Native UI!");
    ui->runEventLoop();
    
    return 0;
}
