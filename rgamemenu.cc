#include <iostream>
#include "rgamemenu.hh"
#include "rgame.hh"

RGameMenu::RGameMenu(int width, int height) : width_{width},
    height_{height}, menuPage_{MenuPage::PAGE_1}, menuState_{MenuState::STAY},
    parent_{nullptr}
{

}

RGameMenu::RGameMenu(int width, int height,
                     std::vector<std::shared_ptr<PageComponent>> menuPages) :
    width_{width}, height_{height}, menuPage_{MenuPage::PAGE_1},
    menuState_{MenuState::STAY}, parent_{nullptr}
{
    pages_ = menuPages;
}

RGameMenu::~RGameMenu()
{
    delete parent_;
}

bool RGameMenu::init()
{
    if ( !terminal_open() ) {
        return false;
    } else {
        terminal_refresh();
        // std::string widthX{std::to_string(width_)};
        // std::string heightY{std::to_string(height_)};
        // std::string windowstring;
        //windowstring = "window.size="+widthX+"x"+heightY+";";
        //terminal_set(windowstring.c_str());
        terminal_set("window.cellsize=auto;");
        terminal_set("window.title='Game Menu';");
        terminal_set("font: ./media/UbuntuMono-R.ttf, size=10x10");
        terminal_set("input: filter={keyboard}");
    }
    return true;
}
// "Game loop" for menu:
void RGameMenu::run()
{
    while ( menuState_ != MenuState::EXIT_MENU ) {

        checkInput();
        render();
        terminal_refresh();
    }

}
// Checks the inputs in the game menu.
void RGameMenu::checkInput()
{
    if ( terminal_has_input() ) {
        int key{terminal_read()};

        switch(key) {
            case TK_1:
                std::cout << "New game" << std::endl;
                parent_->setGameState(RGame::CHAR_CREATION);
                menuState_ = MenuState::EXIT_MENU;
                break;
            case TK_2:
                std::cout << "Previous games" << std::endl;
                parent_->setGameState(RGame::EXIT_GAME);
                menuState_ = MenuState::EXIT_MENU;
                break;
            case TK_3:
                std::cout << "Exit game" << std::endl;
                parent_->setGameState(RGame::EXIT_GAME);
                menuState_ = MenuState::EXIT_MENU;
                break;
            case TK_CLOSE:
                std::cout << "Closed window." << std::endl;
                parent_->setGameState(RGame::EXIT_GAME);
                menuState_ = MenuState::EXIT_MENU;
                break;
            default:
                std::cout << "Unlisted key" << std::endl;
                break;
        }
    }
}
// What is rendered on the menu screen.
void RGameMenu::render()
{
    terminal_clear();
    terminal_color("white");
    terminal_print(4, 1, "[color=orange]GAME MENU[/color]");
    terminal_print(2, 3, "([color=orange]1[/color]) New game");
    terminal_print(2, 5, "([color=orange]2[/color]) Previous games");
    terminal_print(2, 7, "([color=orange]3[/color]) Exit game");

}

void RGameMenu::setState(MenuState state)
{
    menuState_ = state;
}

void RGameMenu::setPage(MenuPage page)
{
    menuPage_ = page;
}

void RGameMenu::setParent(RGame *game)
{
    try {
        parent_ = dynamic_cast<RGame *>(game);
    } catch ( std::bad_cast ) {
        std::cout << "Dynamic cast failed!" << std::endl;
        parent_ = nullptr;
    }
}
