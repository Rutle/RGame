#ifndef DUNGEONMAP_HH
#define DUNGEONMAP_HH
#include <math.h>
#include <time.h>
#include "engine.hh"
#include "tree.hh"
#include "dungeonroom.hh"

namespace GameWorld {

struct Tile {
    int code_;
    bool explored_;
    bool walkable_;
    bool transparent_;
    bool fov_;
    Tile () : code_{35}, explored_{false}, walkable_{false}, transparent_{true}, fov_{false} {}
    bool isExplored() { return explored_; }
    bool isWalkable() { return walkable_; }
    bool isTransparent() { return transparent_; }
    void setProperties(bool isWalkable, bool isTransparent) {
        walkable_ = isWalkable;
        transparent_ = isTransparent;
    }
    void setExplored(bool isExplored) {
        explored_ = isExplored;
    }
    void setFov(bool fov) {
        fov_ = fov;
    }
    bool isInFov() { return fov_; }

};

struct Exit {
    int code_;
    int x_;
    int y_;
};

class DungeonMap {
    public:
        DungeonMap();
        DungeonMap(int width, int height, int levels, int seed);
        void createMap();
        void clearMap();
        // To check if (x, y) is in the vision of the player.
        bool isInFov(int targetX, int targetY);
        // Calculates fov around (x, y).
        void calculateFov(int playerX, int playerY, int radius);
        // Set the properties of particular (x, y) Cell.
        void setProperties(int x, int y, bool isWalkable, bool isTransparent);
        // Check if a tile is walkable.
        bool isWalkable(int targetX, int targetY);
        // Check if a tile is transparent. (let the light pass)
        bool isTransparent(int targetX, int targetY);
        bool isExplored(int targetX, int targetY);
        void setInFox(int x, int y, bool fov);
        Tile &tileAt(int targetX, int targetY);
        std::deque<DungeonRoom> &getRooms();
        int getSeed();
        std::pair<int, int> getRandomLocation(unsigned int room);
    private:
        void createRooms();
        void digRooms();
        void digCorridors(std::shared_ptr<Tree> root);
        void dig(int startX, int startY, int endX, int endY);
        std::shared_ptr<Tree> splitTree(std::shared_ptr<AreaData> container, int level);
        std::pair<std::shared_ptr<AreaData>, std::shared_ptr<AreaData>> splitArea(std::shared_ptr<AreaData> container);
        int width_;
        int height_;
        int levels_;
        int seed_;
        std::shared_ptr<Tree> treeRoot_;
        std::deque<DungeonRoom> rooms_;
        std::vector<Tile> tiles_;
        std::deque<Exit> exits_;


};
} // GameWorld
#endif // DUNGEONMAP_HH
