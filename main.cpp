#include "include/ui_interface.h"
#include <memory>

int main() {
    std::unique_ptr<UIInterface> ui(createNativeUI());
    ui->createWindow();
    ui->showMessage("Hello, Native UI!");
    ui->runEventLoop();
    
    return 0;
}
