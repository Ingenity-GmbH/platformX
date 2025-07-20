#include "application.h"

PXApplicationUniquePtr createApplication() {
    return std::unique_ptr<PXApplication>(new MacOSApplication());
}
