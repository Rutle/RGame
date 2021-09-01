#include "rgame.hh"
#include "rnameinputpage.hh"
#include "rclassinputpage.hh"
#include "rstatinputpage.hh"
#include "rraceinputpage.hh"
#include "rworldgenerator.hh" // Need to include here for unique_ptr in engine
static const std::string CCP[] = {"Name input", "Class choice", "Race choice",
                                  "Stat choices"};
static const std::string CCIds[] = {"Name_input", "Class_input", "Race_input",
                                    "Stat_input"};
RGame::RGame(int width, int height) :
    width_{width}, height_{height}, gameMenu_{nullptr}, charCreation_{nullptr},
    gameEngine_{nullptr}, gameState_{GAME_MENU}
{
    // initGame();

}

int RGame::run(bool gameWorldTest)
{
    if ( gameWorldTest ) {
        gameEngine_ = std::make_shared<GameWorld::Engine>(103, 58);
        gameEngine_->setMapSize(100, 55);
        gameEngine_->initEngine();
        gameEngine_->run();
    } else {
        while ( gameState_ != EXIT_GAME ) {
            if ( gameState_ == GAME_MENU ) {
                gameMenu_->run();
            } else if ( gameState_ == CHAR_CREATION ) {
                charCreation_->init();
                charCreation_->run();
            } else if ( gameState_ == GAME_WORLD ) {
                // engine->run(*this)
            }
        }
    }

    terminal_close();
    return 0;
}

void RGame::initGame()
{
    // terminal_open();
    if ( gameMenu_ == nullptr && charCreation_ == nullptr ) {
        gameMenu_ = std::make_shared<RGameMenu>(RGameMenu{width_, height_});
        gameMenu_->init();
        gameMenu_->setParent(this);
        std::vector<std::shared_ptr<PageComponent>> tempCont;
        tempCont.push_back(std::make_shared<RNameInputPage>(RNameInputPage{CCIds[0], CCP[0]}));
        tempCont.push_back(std::make_shared<RClassInputPage>(RClassInputPage{CCIds[1], CCP[1]}));
        tempCont.push_back(std::make_shared<RRaceInputPage>(RRaceInputPage{CCIds[2], CCP[2]}));
        tempCont.push_back(std::make_shared<RStatInputPage>(RStatInputPage{CCIds[3], CCP[3]}));
        charCreation_ = std::make_shared<RCharacterCreation>(RCharacterCreation{width_, height_, tempCont});
        charCreation_->setParent(this);
    } else {
        gameMenu_->init();
        charCreation_->init();
    }

}

void RGame::setGameState(RGame::GameState state)
{
    gameState_ = state;
}

int RGame::getWindowWidth() const
{
    return width_;
}

int RGame::getWindowHeight() const
{
    return height_;
}
