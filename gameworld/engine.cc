#include <math.h>
#include <time.h>
#include "engine.hh"
#include "rmap.hh"
#include "rgameobjectfactory.hh"
#include "rdungeonfactory.hh"
#include "dataloader.hh"

// #include "rdungeongenerator.hh"


namespace GameWorld {

Engine::Engine() : player_{nullptr}, gameStatus_{STARTUP}, gameState_{STAY},
    map_{nullptr}, width_{120}, height_{40}, mapWidth_{100}, mapHeight_{30},
    generator_{nullptr}
{

}

Engine::Engine(int width, int height) : player_{nullptr}, gameStatus_{STARTUP},
    gameState_{STAY}, map_{nullptr},
    width_{width}, height_{height}, mapWidth_{0}, mapHeight_{0}, generator_{nullptr}
{
    generator_ = std::unique_ptr<RWorldGenerator>(new RWorldGenerator());
}

void Engine::checkInput()
{
    gameStatus_ = IDLE;
    if ( terminal_has_input() ) {
        player_->update();

    }
}
void Engine::update() {
    if ( gameStatus_ == STARTUP ) {
        computeFov();
    }

    if ( gameStatus_ == NEW_TURN ) {
        for ( auto obj : generatedData_.at(map_->getCurrentMapIndex()) ) {
            if ( obj != player_ ) {
                obj->update();
            }
        }
    }

}
void Engine::render() {
    if ( gameStatus_ == NEW_TURN ) {
        terminal_clear();
        terminal_color(color_from_name("#F2F2F2"));
        // 1. Draw borders
        //drawFrame(0, 0, 103, 32);
        // Messages here or something similar above.
        //drawFrame(0, 32, 103, 8);
        //terminal_print(1, 33, "[font=message]You hit Troll for 345 damage.[/font]");
        //terminal_print(1, 34, "[font=message2]You hit Troll for 345 damage.[/font]");
        //terminal_print(1, 35, "[font=message3]You hit Troll for 345 damage.[/font]");
        //terminal_print(1, 36, "[font=message4]You hit Troll for 345 damage.[/font]");
        //terminal_print(1, 37, "[font=message5]You hit Troll for 345 damage.[/font]");
        //terminal_print(1, 38, "[font=message6]You hit Troll for 345 damage.[/font]");
        // 2. Draw map inside its area in the borders.

        map_->render();

        // 3. draw gameobjects (player, monsters and items etc.)
        //player_->render();
        /*
        for ( auto obj : generatedData_.at(map_->getCurrentMapIndex()) ) {
            if ( obj != player_ && (isInFov(obj->getX(), obj->getY()))) {
                obj->render();
            }
        }
        */
        // 4. Draw rest of the GUI here or at the beginning.
    }



}

bool Engine::initEngine() {
    if ( !terminal_open() ) {
        return false;
    } else {
        // width, height
        std::string widthX{std::to_string(width_)};
        std::string heightY{std::to_string(height_)};
        std::string koko;
        koko = "window.size="+widthX+"x"+heightY+";";
        terminal_set(koko.c_str());
        terminal_set("window.cellsize=auto;");
        terminal_set("window.title='Game';");
        //terminal_set("window: size=120x40, cellsize=auto, title='Game'; font=default");
        //terminal_set("window: cellsize=8x12");

        //terminal_set("0xE100: ./Media/terminal8x12_gs_tc.png, size=8x12, spacing=1x1");
        //terminal_set("font: ./Media/UbuntuMono-R.ttf, size=10x18, spacing=2x1");
        //terminal_set("font: ./Media/UbuntuMono-R.ttf, size=8x16");

        //terminal_set("message font: ./Media/UbuntuMono-R.ttf, size=10x12, spacing=1x1");
        //terminal_set("message2 font: ./Media/VeraMono.ttf, size=10x12, spacing=1x1");
        //terminal_set("message3 font: ./Media/VeraMoBd.ttf, size=10x12, spacing=1x1");
        //terminal_set("message4 font: ./Media/ProggyCleanCE.ttf, size=10x12, spacing=1x1");
        //terminal_set("message5 font: ./Media/COURIER.ttf, size=10x12, spacing=1x1");
        //terminal_set("message6 font: ./Media/courier-bold.ttf, size=10x12, spacing=1x1");
        // alkuperäinen koko 13 alapuolella
        terminal_set("font: ./Media/UbuntuMono-R.ttf, size=10, spacing=1x1");
        terminal_refresh();

    }

    gameState_ = STAY;

    // Set up World generator:
    generator_->setDataLoader(DataLoader{});
    generator_->setObjectFactory(RGameObjectFactory{});
    generator_->setDungeonFactory(RDungeonFactory{});
    if (!generator_->initData()) return false;
    generator_->setEngine(this);

    // Set up Player:
    //player_ = std::make_shared<GameObject>(20, 20, 0xE120, "player", "orange");
    player_ = std::make_shared<GameObject>(20, 20, '@', "player", "orange");
    player_->setEngine(this);
    player_->setMovement(std::make_shared<PlayerBehaviour>());

    // Set up first map:
    map_ = std::make_shared<RMap>(mapWidth_, mapHeight_);
    map_->setEngine(this);
    // Voisi olla alustus ekalla mapilla ja sitten normi käyttöön, kun siirrytään
    // seuraavaan mappiin

    map_->addMap(generator_->createDungeon(
                     RWorldGenerator::DungeonTypes::RANDOM, 5, mapWidth_,
                     mapHeight_));
    map_->placePlayer(RMap::PlayerPlacement::FIRST);
    std::list<std::shared_ptr<GameObject>> temp;
    temp.push_back(player_);
    generatedData_.insert({map_->getCurrentMapIndex(), temp});
    generator_->populateDungeon(map_->getCurrentMap(),
                                generatedData_.at(map_->getCurrentMapIndex()),
                                1, 2, false, true);
    std::cout << "Engine init completed!" << std::endl;
    return true;
}

void Engine::changeMap()
{
    // 1. Check if you have to generate new map
    // If yes, populate with monsters and items.
    // Give parameters to dungeon generator for it create correct type of dungeon.

    // If no, change currentmap and current gameobjects.
}

void Engine::setGameStatus(Engine::GameStatus newGameStatus)
{
    gameStatus_ = newGameStatus;
}

void Engine::setGameState(Engine::GameState newGameState)
{
    gameState_ = newGameState;
}
// Used when a monster dies so that their corpse will be shown and if player
// happens to on that tile, player's character will be put over that.
void Engine::moveObjectToFront(std::shared_ptr<GameObject> gameObject)
{
    generatedData_.at(map_->getCurrentMapIndex()).remove(gameObject);
    generatedData_.at(map_->getCurrentMapIndex()).push_front(gameObject);

}

std::list<std::shared_ptr<GameObject> > &Engine::getGameObjects()
{
    return generatedData_.at(map_->getCurrentMapIndex());

}

Engine::GameStatus Engine::getGameStatus() const
{
    return gameStatus_;
}

std::shared_ptr<RMap> &Engine::getMap()
{
    return map_;
}

void Engine::setMapSize(int width, int height)
{
    mapWidth_ = width;
    mapHeight_ = height;
    std::cout << "Map Size set!" << std::endl;
}

std::shared_ptr<GameObject> &Engine::getPlayer()
{
    return player_;
}

bool Engine::isInFov(int targetX, int targetY)
{
    if ( this->getMap()->getCurrentMap()->isInFov(targetX, targetY) ) {
        return true;
    }
    return false;
}

void Engine::computeFov()
{
    map_->getCurrentMap()->calculateFov(player_->getX(), player_->getY(), 5);
}


void Engine::drawFrame(int x, int y, int w, int h)
{

    // terminal_clear_area(x, y, w, h);
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

void Engine::run()
{
    // GameWorld gameloop:
    while ( gameState_ != EXIT_GAME ) {

        checkInput();
        update();
        render();
        terminal_refresh();
    }

}

} // GameWorld
