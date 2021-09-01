#include <math.h>
#include "dungeonroom.hh"

namespace GameWorld {
DungeonRoom::DungeonRoom(std::shared_ptr<AreaData> &data) {
    x_ = data->x_ + (rand()% static_cast<int>((floor(data->width_/3))));
    y_ = data->y_ + (rand()% static_cast<int>((floor(data->height_/3))));
    width_ = data->width_ - (x_ - data->x_);
    height_ = data->height_ - (y_ - data->y_);
    width_ -= rand()% static_cast<int>(floor(width_/3));
    height_ -= rand()% static_cast<int>(floor(height_/3));
}

int DungeonRoom::getX() const
{
    return x_;
}

int DungeonRoom::getY() const
{
    return y_;
}

int DungeonRoom::getWidth() const
{
    return width_;
}

int DungeonRoom::getHeight() const
{
    return height_;
}

int DungeonRoom::getCenterX() const
{
    return (x_ + static_cast<int>(width_/2));
}

int DungeonRoom::getCenterY() const
{
    return (y_ + static_cast<int>(height_/2));
}
} // GameWorld
