#ifndef RRACEINPUTPAGE_HH
#define RRACEINPUTPAGE_HH
#include "BearLibTerminal.h"
#include "pagecomponent.hh"
#include "menucomponent.hh"
#include "rcharactercreation.hh"

class RRaceInputPage : public PageComponent
{
    public:
        RRaceInputPage(std::string id, std::string windowTitle);
        ~RRaceInputPage();
        void render();
        void checkInput(int key);
        void init();
        void setParent(MenuComponent *ccMenu);
    private:
        RCharacterCreation *parent_;
};

#endif // RRACEINPUTPAGE_HH
