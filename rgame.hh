#ifndef RGAME_HH
#define RGAME_HH
#include <iostream>
#include <memory>
#include "rgamemenu.hh"
#include "rcharactercreation.hh"
#include "engine.hh"

class RGame
{
    public:
        enum GameState {
            EXIT_GAME = 0,  // exit game
            GAME_MENU,      // game menu
            CHAR_CREATION,  // char creation
            GAME_WORLD      // game world
        };
        RGame(int width, int height);
        int run(bool gameWorldTest = false);
        void initGame();
        void setGameState(GameState state);
        int getWindowWidth() const;
        int getWindowHeight() const;

    private:
        int width_;
        int height_;
        std::shared_ptr<RGameMenu> gameMenu_;
        std::shared_ptr<RCharacterCreation> charCreation_;
        std::shared_ptr<GameWorld::Engine> gameEngine_;
        GameState gameState_;
        std::vector<std::shared_ptr<MenuComponent>> menus_;



};

#endif // RGAME_HH
