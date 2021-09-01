#ifndef DUNGEONROOM_HH
#define DUNGEONROOM_HH
#include "tree.hh"

namespace GameWorld {
class DungeonRoom {
    public:
        DungeonRoom(std::shared_ptr<AreaData>& data);
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        int getCenterX() const;
        int getCenterY() const;
    private:
        int x_;
        int y_;
        int width_;
        int height_;


};
} // GameWorld
#endif // DUNGEONROOM_HH
