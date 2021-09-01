#include "pagecomponent.hh"

PageComponent::PageComponent(std::string id, std::string windowTitle) :
    id_{id}, windowTitle_{windowTitle}
{
    std::cout << "abstract constructor" << std::endl;
}

void PageComponent::DrawFrame(int x, int y, int w, int h)
{
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

std::string PageComponent::getId() const
{
    return id_;
}

std::string PageComponent::getWindowTitle() const
{
    return windowTitle_;
}
