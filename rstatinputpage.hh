#ifndef RSTATINPUTPAGE_HH
#define RSTATINPUTPAGE_HH
#include <iostream>
#include "pagecomponent.hh"
#include "rcharactercreation.hh"

class RStatInputPage : public PageComponent
{
    public:
        RStatInputPage(std::string id, std::string windowTitle);
        ~RStatInputPage();
        void render();
        void checkInput(int key);
        void init();
        void setParent(MenuComponent *ccMenu);
    private:
        RCharacterCreation *parent_;

};

#endif // RSTATINPUTPAGE_HH
