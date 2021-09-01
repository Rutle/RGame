#include "rcharactercreation.hh"
#include "rgame.hh"
#include "rnameinputpage.hh"

RCharacterCreation::RCharacterCreation() : parent_{nullptr}
{

}

RCharacterCreation::RCharacterCreation(int width, int height,
        std::vector<std::shared_ptr<PageComponent> > &ccPages) :
    width_{width}, height_{height}, menuPage_{MenuPage::PAGE_1},
    menuState_{MenuState::STAY}, name_{L""}, class_{L""}, race_{L""},
    str_{5}, dex_{2}, con_{3}, wis_{4}, parent_{nullptr}
{
    std::cout << "new cc:" << std::endl;
    pages_ = ccPages;

}

RCharacterCreation::~RCharacterCreation()
{
    delete parent_;
}

bool RCharacterCreation::init()
{
    terminal_composition(TK_OFF);
    if ( pages_.size() != 0 ) {
        menuPage_ = MenuPage::PAGE_1;
        menuState_ = MenuState::STAY;
        for ( auto page : pages_ ) {
            page->setParent(this);
        }
        pages_.at(0)->init();
        return true;
    }
    return false;
}

void RCharacterCreation::run()
{
    while ( menuState_ != MenuState::EXIT_MENU ) {
        render();
        checkInput();
        terminal_refresh();
    }
}

void RCharacterCreation::render()
{
    terminal_clear();
    terminal_color("white");
    pages_.at(static_cast<int>(menuPage_))->render();

}

void RCharacterCreation::renderChoices(int x, int y, int w, int h)
{
    DrawFrame(x, y, w, h);
    std::wstring full_name{L"Name: "};
    full_name += name_;
    std::wstring full_class{L"Class: "};
    full_class += class_;
    std::wstring full_race{L"Race: "};
    full_race += race_;
    terminal_wprintf(x+1,y+1, full_name.c_str());
    terminal_wprintf(x+1,y+2, full_class.c_str());
    terminal_wprintf(x+1,y+3, full_race.c_str());
}

void RCharacterCreation::renderStats(int x, int y)
{
    std::string value;
    value = "[[[color=orange]" + std::to_string(str_) + "[/color]]]";
    //sprintf(value, "%d", str_);
    terminal_print(x, y, value.c_str());
    value = "[[[color=orange]" + std::to_string(dex_) + "[/color]]]";
    terminal_print(x, y+1, value.c_str());
    value = "[[[color=orange]" + std::to_string(con_) + "[/color]]]";
    terminal_print(x, y+2, value.c_str());
    value = "[[[color=orange]" + std::to_string(wis_) + "[/color]]]";
    terminal_print(x, y+3, value.c_str());
}

void RCharacterCreation::checkInput()
{
    if ( terminal_has_input() ) {
        int key{terminal_read()};
        if ( key == TK_CLOSE || key == TK_ESCAPE) {
            parent_->setGameState(RGame::EXIT_GAME);
            menuState_ = MenuState::EXIT_MENU;
            return;
        }
        pages_.at(static_cast<int>(menuPage_))->checkInput(key);
    }
}

void RCharacterCreation::setState(MenuState state)
{
    menuState_ = state;
}

void RCharacterCreation::setPage(MenuPage page)
{
    menuPage_ = page;
    pages_.at(static_cast<int>(menuPage_))->init();
}

void RCharacterCreation::setParent(RGame *game)
{
    try {
        parent_ = dynamic_cast<RGame *>(game);
    } catch ( std::bad_cast ) {
        std::cout << "Dynamic cast failed!" << std::endl;
        parent_ = nullptr;
    }
}

void RCharacterCreation::setClass(std::wstring value)
{
    class_ = value;
}

void RCharacterCreation::setRace(std::wstring value)
{
    race_ = value;
}

void RCharacterCreation::setStat(int value, std::string type)
{
    if ( type == "str" ) {
        str_ = value;
    } else if ( type == "dex" ) {
        dex_ = value;
    } else if ( type == "con" ) {
        con_ = value;
    } else if ( type == "wis" ) {
        wis_ = value;
    } else {
        std::cout << "Invalid type!" << std::endl;
    }
}

int RCharacterCreation::getStat(std::string type) const
{
    if ( type == "str" ) {
       return str_;
    } else if ( type == "dex" ) {
        return dex_;
    } else if ( type == "con" ) {
        return con_;
    } else if ( type == "wis" ) {
        return wis_;
    } else {
        std::cout << "Invalid type!" << std::endl;

    }
    return 0;
}

void RCharacterCreation::setName(std::wstring value)
{
    name_ = value;
}
