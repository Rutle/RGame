#ifndef RCHARACTERCREATION_HH
#define RCHARACTERCREATION_HH
#include <memory>
#include <vector>
#include "BearLibTerminal.h"
#include "pagecomponent.hh"
#include "menucomponent.hh"

class RGame;
class RCharacterCreation : public MenuComponent
{
    public:
        RCharacterCreation();
        RCharacterCreation(int width, int height, std::vector<std::shared_ptr<PageComponent>> &ccPages);
        ~RCharacterCreation();
        bool init();
        void run();
        void render();
        void renderChoices(int x, int y, int w, int h);
        void renderStats(int x, int y);
        void checkInput();
        void setState(MenuState state);
        void setPage(MenuPage page);
        void setParent(RGame *game);

        // Temporary setters for choices.
        void setName(std::wstring value);
        void setClass(std::wstring value);
        void setRace(std::wstring value);
        void setStat(int value, std::string type);
        int getStat(std::string type) const;
    private:
        int width_;
        int height_;
        std::vector<std::shared_ptr<PageComponent>> pages_;
        // std::shared_ptr<GameObject> player_;
        MenuPage menuPage_;
        MenuState menuState_;

        // Choices now temporarily as private members
        std::wstring name_;
        std::wstring class_;
        std::wstring race_;
        int str_;
        int dex_;
        int con_;
        int wis_;

        RGame *parent_;
};

#endif // RCHARACTERCREATION_HH
