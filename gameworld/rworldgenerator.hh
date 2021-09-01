#ifndef RWORLDGENERATOR_HH
#define RWORLDGENERATOR_HH
#include "dungeonmap.hh"
#include "gameobject.hh"
#include "rdungeonfactory.hh"
#include "rgameobjectfactory.hh"

namespace GameWorld {
class Engine;
class DungeonMap;
class RDungeonFactory;
class RWorldGenerator
{
    public:
        enum DungeonTypes {
            RANDOM = 0,
            CIRCULAR,
            WORLD,
            TOWN
        };
        RWorldGenerator();
        RWorldGenerator(DataLoader loader, RGameObjectFactory gfactory,
                        RDungeonFactory dfactory, Engine *engine);
        ~RWorldGenerator();
        bool initData();
        std::shared_ptr<DungeonMap> createDungeon(DungeonTypes type, int levels, int width,
                                  int height);
        void populateDungeon(const std::shared_ptr<DungeonMap> &map,
                             std::list<std::shared_ptr<GameObject>> &objects,
                             int monsterLvl, int objectsPerRoom,
                             bool items, bool monsters);
        void setDataLoader(DataLoader loader);
        void setObjectFactory(RGameObjectFactory factory);
        void setDungeonFactory(RDungeonFactory factory);
        void setEngine(Engine *engine);

    private:
        std::shared_ptr<DataLoader> loader_;
        std::unique_ptr<RGameObjectFactory> gFactory_;
        std::unique_ptr<RDungeonFactory> dFactory_;
        Engine *engine_;

};
}   // GameWorld
#endif // RWORLDGENERATOR_HH
