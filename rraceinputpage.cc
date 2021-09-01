#include "rraceinputpage.hh"
#include "rcharactercreation.hh"
RRaceInputPage::RRaceInputPage(std::string id, std::string windowTitle) :
    PageComponent(id, windowTitle), parent_{nullptr}
{
    std::cout << "race input constructor" << std::endl;
}

RRaceInputPage::~RRaceInputPage()
{
    terminal_clear();
    delete parent_;
}

void RRaceInputPage::render()
{
    terminal_clear();
    terminal_print(2, 3, "Choose race:");
    terminal_print(4, 5, "([color=orange]1[/color]) Human");
    terminal_print(4, 6, "([color=orange]2[/color]) Dwarf");
    terminal_print(4, 7, "([color=orange]3[/color]) Orc");
    parent_->renderChoices(50, 2, 17, 10);
    terminal_refresh();
}

void RRaceInputPage::checkInput(int key)
{
    if ( key == TK_CLOSE || key == TK_ESCAPE ) {
        parent_->setState(MenuComponent::MenuState::EXIT_MENU);
    } else if ( key == TK_1 ) {
        parent_->setRace(L"Human");
        parent_->setPage(MenuComponent::MenuPage::PAGE_4);
    } else if ( key == TK_2 ) {
        parent_->setRace(L"Dwarf");
        parent_->setPage(MenuComponent::MenuPage::PAGE_4);
    } else if ( key == TK_3 ) {
        parent_->setRace(L"Orc");
        parent_->setPage(MenuComponent::MenuPage::PAGE_4);
    }
}

void RRaceInputPage::init()
{
    std::string temp{"window.title='"};
    temp += getWindowTitle();
    temp += "';";
    terminal_set(temp.c_str());
    // terminal_set("window.title='Character Creation: Race choices.';");

}

void RRaceInputPage::setParent(MenuComponent *ccMenu)
{
    try {
        parent_ = dynamic_cast<RCharacterCreation *>(ccMenu);
    } catch ( std::bad_cast ) {
        std::cout << "Dynamic cast failed!" << std::endl;
        parent_ = nullptr;
    }
}
