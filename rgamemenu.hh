#ifndef RGAMEMENU_HH
#define RGAMEMENU_HH
#include <memory>
#include <vector>
#include "BearLibTerminal.h"
#include "pagecomponent.hh"
#include "menucomponent.hh"

class RGame;

class RGameMenu : public MenuComponent
{
    public:
        RGameMenu(int width, int height);
        RGameMenu(int width, int height, std::vector<std::shared_ptr<PageComponent>> menuPages);
        ~RGameMenu();
        bool init();
        void run();
        void checkInput();
        void render();
        void setState(MenuState state);
        void setPage(MenuPage page);
        void setParent(RGame *game);
    private:
        int width_;
        int height_;
        MenuPage menuPage_;
        MenuState menuState_;
        std::vector<std::shared_ptr<PageComponent>> pages_;
        RGame *parent_;
};

#endif // GAMEMENU_HH
