#include "rstatinputpage.hh"
#include "menucomponent.hh"
#include "rcharactercreation.hh"

RStatInputPage::RStatInputPage(std::string id, std::string windowTitle) :
    PageComponent(id, windowTitle), parent_{nullptr}
{
    std::cout << "stat input constructor" << std::endl;
}

RStatInputPage::~RStatInputPage()
{
    terminal_clear();
    delete parent_;
}

void RStatInputPage::render()
{
    terminal_clear();
    terminal_print(2, 3, "Choose stats:");
    terminal_print(4, 5, "([color=orange]1[/color]) Strength");
    terminal_print(4, 6, "([color=orange]2[/color]) Dexterity");
    terminal_print(4, 7, "([color=orange]3[/color]) Constitution");
    terminal_print(4, 8, "([color=orange]4[/color]) Wisdom");
    terminal_print(4, 10, "([color=orange]Up[/color]) Increase stat.");
    terminal_print(4, 11, "([color=orange]Down[/color]) Decrease stat.");
    terminal_print(4, 12, "([color=orange]Number[/color]) Select stat.");
    parent_->renderChoices(50, 2, 17, 10);
    std::string value;
    value = "[[[color=orange]" + std::to_string(parent_->getStat("str")) + "[/color]]]";
    //sprintf(value, "%d", str_);
    terminal_print(26, 5, value.c_str());
    value = "[[[color=orange]" + std::to_string(parent_->getStat("dex")) + "[/color]]]";
    terminal_print(26, 6, value.c_str());
    value = "[[[color=orange]" + std::to_string(parent_->getStat("con")) + "[/color]]]";
    terminal_print(26, 7, value.c_str());
    value = "[[[color=orange]" + std::to_string(parent_->getStat("wis")) + "[/color]]]";
    terminal_print(26, 8, value.c_str());
    // parent_->renderStats(26, 5);
    terminal_refresh();
}

void RStatInputPage::checkInput(int key)
{
    if ( key == TK_CLOSE || key == TK_ESCAPE ) {
        parent_->setState(MenuComponent::MenuState::EXIT_MENU);
    } else if ( key == TK_1 ) {
        int nmb{parent_->getStat("str")};
        std::string value;
        std::cout << "TK_1";
        value = "[color=dark orange]" + std::to_string(nmb) + "[/color]";
        terminal_print(27, 5, value.c_str());
        terminal_refresh();
        while ( true ) {
            int key = terminal_read();
            if ( key == TK_ESCAPE || key == TK_CLOSE || key == TK_RETURN ) {
                break;
            } else if ( key == TK_UP ) {
                std::cout << "TK_UP";
                nmb += 1;
            } else if ( key == TK_DOWN ) {
                std::cout << "TK_DOWN";
                if ( nmb != 0) {
                    nmb -= 1;
                }
            }
            value = "[color=dark orange]" + std::to_string(nmb) + "[/color]";
            terminal_print(27, 5, value.c_str());
            terminal_refresh();
        }


    } else if ( key == TK_2 ) {
        int nmb{0};
        std::string value;
        std::cout << "TK_1";
        while ( true ) {
            int key = terminal_read();
            if ( key == TK_ESCAPE || key == TK_CLOSE || key == TK_RETURN ) {
                break;
            } else if ( key == TK_UP ) {
                std::cout << "TK_UP";
                nmb += 1;
            } else if ( key == TK_DOWN ) {
                std::cout << "TK_DOWN";
                if ( nmb != 0) {
                    nmb -= 1;
                }
            }
            value = "[color=dark orange]" + std::to_string(nmb) + "[/color]";
            terminal_print(27, 6, value.c_str());
            terminal_refresh();
        }
    } else if ( key == TK_3 ) {
        int nmb{0};
        std::string value;
        std::cout << "TK_1";
        while ( true ) {
            int key = terminal_read();
            if ( key == TK_ESCAPE || key == TK_CLOSE || key == TK_RETURN ) {
                break;
            } else if ( key == TK_UP ) {
                std::cout << "TK_UP";
                nmb += 1;
            } else if ( key == TK_DOWN ) {
                std::cout << "TK_DOWN";
                if ( nmb != 0) {
                    nmb -= 1;
                }
            }
            value = "[color=dark orange]" + std::to_string(nmb) + "[/color]";
            terminal_print(27, 7, value.c_str());
            terminal_refresh();
        }
    } else if ( key == TK_4 ) {
        int nmb{0};
        std::string value;
        std::cout << "TK_1";
        while ( true ) {
            int key = terminal_read();
            if ( key == TK_ESCAPE || key == TK_CLOSE || key == TK_RETURN ) {
                break;
            } else if ( key == TK_UP ) {
                std::cout << "TK_UP";
                nmb += 1;
            } else if ( key == TK_DOWN ) {
                std::cout << "TK_DOWN";
                if ( nmb != 0) {
                    nmb -= 1;
                }
            }
            value = "[color=dark orange]" + std::to_string(nmb) + "[/color]";
            terminal_print(27, 8, value.c_str());
            terminal_refresh();
        }
    }
}

void RStatInputPage::init()
{
    std::string temp{"window.title='"};
    temp += getWindowTitle();
    temp += "';";
    terminal_set(temp.c_str());
    // terminal_set("window.title='Character Creation: Input name.';");
}

void RStatInputPage::setParent(MenuComponent *ccMenu)
{
    try {
        parent_ = dynamic_cast<RCharacterCreation *>(ccMenu);
    } catch ( std::bad_cast ) {
        std::cout << "Dynamic cast failed!" << std::endl;
        parent_ = nullptr;
    }

}
