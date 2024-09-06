#include <memory>
#include "include/ui_interface.h"

int main() {
    std::unique_ptr<UIInterface> ui(createUI());
    ui->createWindow("platformX App");
    ui->runEventLoop();
    
    return EXIT_SUCCESS;
}
