#include "rdungeonfactory.hh"
namespace GameWorld {

RDungeonFactory::RDungeonFactory() : data_{nullptr}
{

}

RDungeonFactory::RDungeonFactory(DataLoader &data) : data_{nullptr}
{
    data_ = std::make_shared<DataLoader>(data);
}

DungeonMap RDungeonFactory::createRandomDungeon(int levels, int width, int height)
{
    int seed = time(NULL);
    srand(seed);
    DungeonMap newDungeon{width, height, levels, seed};
    newDungeon.createMap();
    return newDungeon;
}

void RDungeonFactory::setData(std::shared_ptr<DataLoader> data)
{
    data_ = data;
}
} // GameWorld
