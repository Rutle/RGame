#ifndef RNAMEINPUTPAGE_HH
#define RNAMEINPUTPAGE_HH
#include "BearLibTerminal.h"
#include "pagecomponent.hh"
#include "menucomponent.hh"
#include "rcharactercreation.hh"

class RNameInputPage : public PageComponent
{
    public:
        RNameInputPage(std::string id, std::string windowTitle);
        ~RNameInputPage();
        void render();
        void checkInput(int key);
        void init();
        void setParent(MenuComponent *ccMenu);
    private:
        int max_chars_;
        wchar_t *buffer_;
        wchar_t character_;
        int result_;
        std::wstring s;
        int max;
        RCharacterCreation *parent_;
};

#endif // RNAMEINPUTPAGE_HH
