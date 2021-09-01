#ifndef PAGECOMPONENT_HH
#define PAGECOMPONENT_HH
#include <iostream>
#include <memory>
#include "BearLibTerminal.h"

class MenuComponent;
class PageComponent {
    public:
        PageComponent() = default;
        PageComponent(std::string id, std::string windowTitle_);
        virtual ~PageComponent() = default;
        virtual void render() = 0;
        virtual void checkInput(int key) = 0;
        virtual void init() = 0;
        virtual void setParent(MenuComponent *ccMenu) = 0;
    protected:
        virtual void DrawFrame(int x, int y, int w, int h);
        std::string getId() const;
        std::string getWindowTitle() const;
        std::string id_;
        std::string windowTitle_;


};

#endif // PAGECOMPONENT_HH
