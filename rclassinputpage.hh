#ifndef RCLASSINPUTPAGE_HH
#define RCLASSINPUTPAGE_HH
#include <iostream>
#include "pagecomponent.hh"
#include "rcharactercreation.hh"

class RClassInputPage : public PageComponent
{
    public:
        RClassInputPage(std::string id, std::string windowTitle);
        ~RClassInputPage();
        void render();
        void checkInput(int key);
        void init();
        void setParent(MenuComponent *ccMenu);
    private:
        RCharacterCreation *parent_;
};

#endif // RCLASSINPUTPAGE_HH
