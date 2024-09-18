#pragma once

#include "include/global.h"

#include <string>
#include <functional>
#include <vector>
#include <memory>

#pragma region PXComponent
class PXComponent {
    public:
        PXComponent(const std::string& title, const PXSize& size, const PXPosition& position, const PXType& type=NONE);
        virtual ~PXComponent() = default;
        void addComponent(PXComponent* component);
        PXHandle getHandle() const;
        PXHandle getParent() const;
        PXPosition getPosition() const;
        PXSize getSize() const;
        PXType getType() const;
        std::vector<PXComponent*> getComponents() const;

    protected:
        std::string title;
        PXSize size;
        PXPosition position;
        PXType type;
        PXHandle handle;
        PXHandle parent;
        std::vector<PXComponent*> components;
};
#pragma endregion PXComponent
