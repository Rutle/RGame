#include <iostream>
#include "rmap.hh"

static const bool RANDOMROOM = false;  // Place player in a random room.
static const bool FIRSTROOM = true;    // Place player in the first room.
const int HOFFSET = 1;
const int WOFFSET = 1;

namespace GameWorld {

RMap::RMap(int width, int height) : width_{width}, height_{height},/*
    mapData_{nullptr}, */ engine_{nullptr}, currentMap_{0}
{
    std::cout << "New RMap created [Constructor]." << std::endl;

}

RMap::~RMap()
{
    delete engine_;
}

void RMap::render()
{

    for ( int y = 0; y < height_; ++y ) {
        for ( int x = 0; x < width_; ++x ) {
            //terminal_put(x, y, mapData_.at(currentMap_)->tileAt(x, y).code_);
            // terminal_put(x, y, mapData_)
            /*
            if ( mapData_.at(currentMap_)->isWalkable(x, y) ) {
                terminal_put(x, y, 0xE10C);
            } else {
                terminal_put(x, y, 0xE103);
            }*/
            if ( isWall(x, y) ) {
                terminal_color(color_from_name("#F2F2F2"));
                terminal_put(x+WOFFSET, y+HOFFSET, '#');
            } else {
                terminal_color(color_from_name("#F2F2F2"));
                terminal_put(x+WOFFSET, y+HOFFSET, '.');
            }
            /*if ( mapData_.at(currentMap_)->isInFov(x, y) ) {
                if ( isWall(x, y) ) {
                    terminal_color(color_from_name("#F2F2F2"));
                    terminal_put(x+WOFFSET, y+HOFFSET, '#');
                } else {
                    terminal_color(color_from_name("#F2F2F2"));
                    terminal_put(x+WOFFSET, y+HOFFSET, '.');
                }
            } else if ( mapData_.at(currentMap_)->tileAt(x, y).explored_ ) {
                if ( isWall(x, y) ) {

                    terminal_color(color_from_name("#707070"));
                    terminal_put(x+WOFFSET, y+HOFFSET, '#');
                    terminal_color(color_from_name("#F2F2F2"));
                } else {
                    terminal_color(color_from_name("#707070"));
                    terminal_put(x+WOFFSET, y+HOFFSET, '.');
                    terminal_color(color_from_name("#F2F2F2"));
                }
            }*/

        }
    }
}

void RMap::setEngine(Engine *engine)
{
    try {
        engine_ = engine;
    } catch ( const char* msg ) {
        std::cerr << msg << std::endl;
        engine_ = nullptr;
    }
    std::cout << "DungeonMap: Engine set!" << std::endl;
}

bool RMap::isWall(int targetX, int targetY)
{
    return !mapData_.at(currentMap_)->isWalkable(targetX, targetY);
}

void RMap::addMap(std::shared_ptr<DungeonMap> newDungeon)
{
    try {
        mapData_.push_back(newDungeon);
    } catch ( const char* msg ) {
        std::cerr << msg << std::endl;
        mapData_.push_back(nullptr);
    }
}

void RMap::placePlayer(PlayerPlacement location)
{
    // Place player in a room. Should be used when new map has been generated
    // and as player is about to enter it for the first time. For example
    // going down the stairs to a newly generated map, but when moving between
    // already explored maps, it should be to the position of the stairs.
    int centerX;
    int centerY;
    switch (location) {
        case FIRST:
        {
            centerX = mapData_.at(currentMap_)->getRooms().at(0).getCenterX();
            centerY = mapData_.at(currentMap_)->getRooms().at(0).getCenterY();
        }
            break;
        case RANDOM:
        {
            unsigned int roomCount{mapData_.at(currentMap_)->getRooms().size()};
            int roomNmb{rand()% static_cast<int>(roomCount)};
            std::cout << roomNmb << std::endl;
            centerX = mapData_.at(currentMap_)->getRooms().at(roomNmb).getCenterX();
            centerY = mapData_.at(currentMap_)->getRooms().at(roomNmb).getCenterY();
        }
            break;
        case STAIRS:
            break;

        default:
            break;
    }

    std::cout << "Place player at x:[" << centerX << "] y:[" << centerY << "]" << std::endl;
    engine_->getPlayer()->setLocation(centerX, centerY);
}

int RMap::getCurrentMapIndex() const
{
    return currentMap_;
}


std::shared_ptr<DungeonMap> RMap::getCurrentMap()
{
    return mapData_.at(currentMap_);

}

void RMap::changeDungeon()
{

}


} // GameWorld
