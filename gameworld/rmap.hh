#ifndef RMAP_HH
#define RMAP_HH
#include <memory>
#include <math.h>
#include <time.h>
#include "dungeonmap.hh"
#include "engine.hh"


namespace GameWorld {
// Contains pointer to map and its rendering.
class RMap
{
    public:
        // Player's placement in the center of random or first room, or at stairs.
        enum PlayerPlacement {
            RANDOM = 0,         // Random room.
            FIRST = 1,          // First room
            STAIRS = 2          // Place at stairs.
        };

        RMap(int width, int height);
        ~RMap();
        void render();
        void setEngine(Engine *engine);
        bool isWall(int targetX, int targetY);
        void addMap(std::shared_ptr<DungeonMap> newDungeon);
        void placePlayer(RMap::PlayerPlacement location);
        int getCurrentMapIndex() const;
        std::shared_ptr<DungeonMap> getCurrentMap();
        void changeDungeon();
        int getSeed();
    private:
        int width_;
        int height_;
        std::vector<std::shared_ptr<DungeonMap>> mapData_;
        Engine *engine_;
        int currentMap_;


};
} // GameWorld
#endif // RMAP_HH
