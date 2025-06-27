#pragma once

#include "include/global.h"

#include <string>
#include <functional>
#include <vector>
#include <memory>

#pragma region PXControl
class LIB PXControl {
    public:
        PXControl(const std::string& title, const PXPosition& position, const PXSize& size, const PXType& type=NONE);
        virtual ~PXControl() = default;
        void addControl(PXControl* control);
        PXHandle getHandle() const;
        PXHandle getParent() const;
        PXPosition getPosition() const;
        PXSize getSize() const;
        PXType getType() const;
        void setTitle(const std::string& title);
        std::string getTitle();
        std::vector<PXControl*> getControls() const;
        virtual bool hasCallback() const = 0;

    protected:
        std::string title;
        PXPosition position;
        PXSize size;
        PXType type;
        PXHandle handle;
        PXHandle parent;
        std::vector<PXControl*> controls;
};
#pragma endregion PXControl
