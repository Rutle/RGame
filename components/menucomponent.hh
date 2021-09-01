#ifndef MENUCOMPONENT_HH
#define MENUCOMPONENT_HH
#include "BearLibTerminal.h"
class RGame;
class MenuComponent {
    public:
        enum class MenuPage : int {
            PAGE_1 = 0,     // Page 1
            PAGE_2 = 1,     // Page 2
            PAGE_3 = 2,     // Page 3
            PAGE_4 = 3,     // Page 4
            PAGE_5 = 4,     // Page 5
            PAGE_6 = 5      // Page 6
        };
        enum class MenuState : int {
            STAY = 0,           // stay in menu
            EXIT_MENU = 1,      // Exit menu
        };
        MenuComponent() = default;
        virtual ~MenuComponent() = default;
        virtual bool init() = 0;
        virtual void run() = 0;
        virtual void checkInput() = 0;
        virtual void render() = 0;
        virtual void setState(MenuState state) = 0;
        virtual void setPage(MenuPage page) = 0;
        virtual void setParent(RGame *game) = 0;
    protected:
        virtual void DrawFrame(int x, int y, int w, int h) {
            terminal_clear_area(x, y, w, h);
            for ( int i = x; i < x + w; ++i ) {
                terminal_put(i, y, L'─');
                terminal_put(i, y+h-1, L'─');
            }
            for ( int j = y; j < y + h; ++j ) {
                terminal_put(x, j, L'│');
                terminal_put(x+w-1, j, L'│');
            }

            terminal_put(x, y, L'┌');
            terminal_put(x+w-1, y, L'┐');
            terminal_put(x, y+h-1, L'└');
            terminal_put(x+w-1, y+h-1, L'┘');
        }

};

#endif // MENUCOMPONENT_HH
