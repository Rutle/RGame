#include <utility>
#include "rworldgenerator.hh"
const int HOFFSET = 1;
const int WOFFSET = 1;
namespace GameWorld {
RWorldGenerator::RWorldGenerator() : loader_{nullptr}, gFactory_{nullptr},
    dFactory_{nullptr}, engine_{nullptr}
{

}

RWorldGenerator::~RWorldGenerator()
{
    delete engine_;
}

RWorldGenerator::RWorldGenerator(DataLoader loader,
                                 RGameObjectFactory gfactory,
                                 RDungeonFactory dfactory,
                                 Engine *engine) :
    loader_{nullptr}, gFactory_{nullptr}, dFactory_{nullptr}, engine_{nullptr}

{

    loader_ = std::make_shared<DataLoader>(loader);
    gFactory_ = std::unique_ptr<RGameObjectFactory>(new RGameObjectFactory{gfactory});
    dFactory_ = std::unique_ptr<RDungeonFactory>(new RDungeonFactory{dfactory});
    gFactory_->setData(loader_);
    dFactory_->setData(loader_);
    // loader_->init();
    engine_ = engine;
}

bool RWorldGenerator::initData()
{
    if (!loader_->init()) {
        std::cout << "DataLoader init failed!" << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<DungeonMap> RWorldGenerator::createDungeon(
        RWorldGenerator::DungeonTypes type, int levels, int width, int height)
{
    std::shared_ptr<DungeonMap> newDungeon;
    if ( type == RANDOM ) {
        newDungeon = std::make_shared<DungeonMap>(
                    dFactory_->createRandomDungeon(levels, width, height));
    }
    return newDungeon;
}

void RWorldGenerator::populateDungeon(const std::shared_ptr<DungeonMap> &map,
                               std::list<std::shared_ptr<GameObject>> &objects,
                                        int monsterLvl, int maxObjects,
                                        bool items, bool monsters)
{
    // unsigned int roomCount{map->getRooms().size()};

    std::map<std::pair<int, int>, bool> checkList_;
    srand(map->getSeed());
    int x;
    int y;
    std::pair<int, int> tempLoc;
    int playerX{objects.front()->getX()};
    int playerY{objects.front()->getY()};
    // std::cout << "Player at: [" << objects.front()->getX() << "], [" << objects.front()->getY() << "]" << std::endl;
    for ( auto room : map->getRooms() ) {
        // std::cout << "Room x: [" << room.getX() << "] y: [" << room.getY() << "] width: [" << room.getWidth() << "] height: [" << room.getHeight() << "]" << std::endl;
        for (int i = 0; i < rand() % maxObjects + 1; ++i ) {
            x = room.getX() + rand() % room.getWidth();
            y = room.getY() + rand() % room.getHeight();
            tempLoc = std::make_pair(x, y);
            if ( checkList_.find(tempLoc) != checkList_.end() || (x == playerX && y == playerY)) {
                // randomi uudestaan
                std::cout << "Monster already at: [" << x << "], [" << y << "]" << std::endl;
                x = room.getX() + rand() % room.getWidth();
                y = room.getY() + rand() % room.getHeight();
                tempLoc = std::make_pair(x, y);
                while ( checkList_.find(tempLoc) != checkList_.end() || (x == playerX && y == playerY )) {
                    x = room.getX() + rand() % room.getWidth();
                    y = room.getY() + rand() % room.getHeight();
                    tempLoc = std::make_pair(x, y);
                    std::cout << "generated new location!" << std::endl;
                }

            }
            checkList_.insert({tempLoc, true});
            //std::cout << "New monster at x: [" << x << "]" << " y: [" << y << "]" << std::endl;
        }
    }

    for ( auto xyPair : checkList_ ) {
        //std::shared_ptr<GameObject> newOB = std::make_shared<GameObject>(gFactory_->createMonster(Data::MonsterTypes::HUMANOID));
        //std::cout << "the beginning of loop" << std::endl;
        //GameObject newOB{};
        //std::cout << "NEWOBJ created" << std::endl;
        //newOB->setLocation(xyPair.first.first, xyPair.first.second);
        //std::cout << "NEWOBJ location set" << std::endl;
        //newOB->setEngine(engine_);
        //std::cout << "NEWOBJ engine set" << std::endl;
        //objects.push_back(newOB);
        //std::cout << "NEWOBJ pushed" << std::endl;
        GameObject newOB{gFactory_->createMonster(Data::MonsterTypes::HUMANOID)};
        newOB.setLocation(xyPair.first.first, xyPair.first.second);
        newOB.setEngine(engine_);
        objects.push_back(std::make_shared<GameObject>(newOB));
        std::cout << "Monster [" << newOB.getName() << "] x:[" << newOB.getX() << "] y:[" << newOB.getY() << "]" << std::endl;
    }
    //GameObject newOB(gFactory_->createMonster(Data::MonsterTypes::HUMANOID));
    //newOB.setLocation(tempLoc.first, tempLoc.second);
    //newOB.setEngine(engine_);
    //objects.push_back(std::make_shared<GameObject>(newOB));
    //std::cout << "end" << std::endl;
    //GameObject newOB{gFactory_->createMonster(Data::MonsterTypes::HUMANOID)};
    //objects.push_back(std::make_shared<GameObject>(newOB));

}

void RWorldGenerator::setDataLoader(DataLoader loader)
{
    loader_ = std::make_shared<DataLoader>(loader);
}

void RWorldGenerator::setObjectFactory(RGameObjectFactory factory)
{
    if ( gFactory_ == nullptr ) {
        gFactory_ = std::unique_ptr<RGameObjectFactory>(new RGameObjectFactory{factory});
    } else {
        gFactory_ = std::move(std::unique_ptr<RGameObjectFactory>(new RGameObjectFactory{factory}));
    }
    gFactory_->setData(loader_);
}

void RWorldGenerator::setDungeonFactory(RDungeonFactory factory)
{
    if ( dFactory_ == nullptr ) {
        dFactory_ = std::unique_ptr<RDungeonFactory>(new RDungeonFactory{factory});
    } else {
        dFactory_ = std::move(std::unique_ptr<RDungeonFactory>(new RDungeonFactory{factory}));
    }
    dFactory_->setData(loader_);
}

void RWorldGenerator::setEngine(Engine *engine)
{
    engine_ = engine;
}

} // GameWorld
