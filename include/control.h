#pragma once

#include "include/global.h"

#include <string>
#include <functional>
#include <vector>
#include <memory>

#pragma region PXControl
class LIB PXControl : public std::enable_shared_from_this<PXControl> {
    public:
        PXControl(const PXString& title, const PXPosition& position, const PXSize& size, const PXType& type=NONE);
        ~PXControl();
        void addControl(PXControl* control);
        PXHandle getHandle() const;
        PXControl* getParent();
        virtual void setPosition(const PXPosition& position);
        virtual PXPosition getPosition();
        virtual void setSize(const PXSize& size);
        virtual PXSize getSize();
        PXType getType() const;
        void setTitle(const PXString& title);
        PXString getTitle();
        std::vector<PXControl*> getControls() const;
        virtual bool hasCallback() const = 0;

    protected:
        PXString title;
        PXPosition position;
        PXSize size;
        PXType type;
        PXHandle handle;
        PXControl* parent;
        std::vector<PXControl*> controls;
};
using PXControlSharedPtr = std::shared_ptr<PXControl>;
#pragma endregion PXControl
