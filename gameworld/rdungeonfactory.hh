#ifndef RDUNGEONFACTORY_HH
#define RDUNGEONFACTORY_HH
#include <memory>
#include <dungeonmap.hh>
#include "rdata.hh"
#include "dataloader.hh"

namespace GameWorld {
class DungeonMap;
class RDungeonFactory
{
    public:
        RDungeonFactory();
        RDungeonFactory(DataLoader &data);
        DungeonMap createRandomDungeon(int levels, int width, int height);
        void setData(std::shared_ptr<DataLoader> data);
    private:
        std::shared_ptr<DataLoader> data_;
};
} // GameWorld
#endif // RDUNGEONFACTORY_HH
