#include <vector>
#include <iostream>
#include "menucomponent.hh"
#include "rnameinputpage.hh"
#include "rcharactercreation.hh"

RNameInputPage::RNameInputPage(std::string id, std::string windowTitle) :
    PageComponent(id, windowTitle), max_chars_{32}, character_{L' '},
    result_{0}, max{32}, parent_{nullptr}

{

    buffer_ = new wchar_t [max_chars_+1];
    buffer_[0] = 0;
    std::cout << "name input constructor" << std::endl;


}

RNameInputPage::~RNameInputPage()
{
    terminal_clear();
    delete buffer_;
    delete parent_;
}

void RNameInputPage::render()
{
    terminal_clear();
    terminal_print(2, 3, "Name:");
    DrawFrame(8, 2, max_chars_+2, 3);
    parent_->renderChoices(50, 2, 17, 10);
    terminal_wprintf(9, 3, L"%-*ls", max, s.c_str());
    terminal_refresh();
}

void RNameInputPage::checkInput(int key)
{
    if ( key == TK_RETURN ) {
        parent_->setName(s);
        parent_->setPage(MenuComponent::MenuPage::PAGE_2);
    } else if ( key == TK_BACKSPACE && s.length() > 0 ) {
        s.resize(s.length()-1);
    } else if ( terminal_check(TK_WCHAR) && s.length() < max ) {
        s += (wchar_t)terminal_state(TK_WCHAR);
    } else if ( key == TK_ESCAPE || key == TK_CLOSE ) {
        parent_->setState(MenuComponent::MenuState::EXIT_MENU);
    }
}

void RNameInputPage::init()
{
    std::string temp{"window.title='"};
    temp += getWindowTitle();
    temp += "';";
    // terminal_set("window.title='Character Creation: Input name.';");
    terminal_set(temp.c_str());
    buffer_[0] = {0};
    result_ = 0;
}

void RNameInputPage::setParent(MenuComponent *ccMenu)
{
    try {
        parent_ = dynamic_cast<RCharacterCreation *>(ccMenu);
    } catch ( std::bad_cast ) {
        std::cout << "Dynamic cast failed!" << std::endl;
        parent_ = nullptr;
    }
}


