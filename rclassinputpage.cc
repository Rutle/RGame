#include "rclassinputpage.hh"
#include "menucomponent.hh"
#include "rcharactercreation.hh"
RClassInputPage::RClassInputPage(std::string id, std::string windowTitle) :
    PageComponent(id, windowTitle), parent_{nullptr}
{
    std::cout << "race input constructor" << std::endl;
}

RClassInputPage::~RClassInputPage()
{
    terminal_clear();
    delete parent_;
}

void RClassInputPage::render()
{
    terminal_clear();
    terminal_print(2, 3, "Choose class:");
    terminal_print(4, 5, "([color=orange]1[/color]) Warrior");
    terminal_print(4, 6, "([color=orange]2[/color]) Mage");
    terminal_print(4, 7, "([color=orange]3[/color]) Rogue");
    parent_->renderChoices(50, 2, 17, 10);
    terminal_refresh();
}

void RClassInputPage::checkInput(int key)
{
    if ( key == TK_CLOSE || key == TK_ESCAPE ) {
        parent_->setState(MenuComponent::MenuState::EXIT_MENU);
    } else if ( key == TK_1 ) {
        parent_->setPage(MenuComponent::MenuPage::PAGE_3);
        parent_->setClass(L"Warrior");
    } else if ( key == TK_2 ) {
        parent_->setPage(MenuComponent::MenuPage::PAGE_3);
        parent_->setClass(L"Mage");
    } else if ( key == TK_3 ) {
        parent_->setPage(MenuComponent::MenuPage::PAGE_3);
        parent_->setClass(L"Rogue");
    }
}

void RClassInputPage::init()
{
    std::string temp{"window.title='"};
    temp += getWindowTitle();
    temp += "';";
    terminal_set(temp.c_str());
    // terminal_set("window.title='Character Creation: Choose a class';");
}

void RClassInputPage::setParent(MenuComponent *ccMenu)
{
    try {
        parent_ = dynamic_cast<RCharacterCreation *>(ccMenu);
    } catch ( std::bad_cast ) {
        std::cout << "Dynamic cast failed!" << std::endl;
        parent_ = nullptr;
    }
}
