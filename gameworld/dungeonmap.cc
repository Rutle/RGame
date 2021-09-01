#include "dungeonmap.hh"

namespace GameWorld {

const int MIN_WIDTH = 5; // Osa-alueen minimileveys.
const int MIN_HEIGHT = 5; // Osa-alueen minimikorkeus.

const bool RATIO = true;
const double HRATIO = 0.45;
const double WRATIO = 0.45;

DungeonMap::DungeonMap()
{

}

DungeonMap::DungeonMap(int width, int height, int levels, int seed) : width_{width},
    height_{height}, levels_{levels}, seed_{seed}, treeRoot_{nullptr},
    tiles_{{(static_cast<unsigned int>(width*height))}}
{
}

// Funktio, joka rakentaa luolaston.
void DungeonMap::createMap() {
    std::shared_ptr<AreaData> data =
            std::make_shared<AreaData>(0, 0, width_, height_);
    treeRoot_ = splitTree(data, levels_);
    createRooms();
    digRooms();
    digCorridors(treeRoot_);
}

// Rekursiivinen funktio, joka rakentaa BSP-puurakenteen.
std::shared_ptr<Tree> DungeonMap::splitTree(
        std::shared_ptr<AreaData> area, int level)
{
    // Asetetaan lähtökohta puulle.
    std::shared_ptr<Tree> root = std::make_shared<Tree>(area);
    if ( level != 0 ) {
        std::pair<std::shared_ptr<AreaData>, std::shared_ptr<AreaData>> areas;
        areas = splitArea(area);
        // Alue ei ole tarpeeksi iso jakamiselle, jolloin tästä tehdään lehti.
        if ( areas.first == nullptr && areas.second == nullptr ) {
            root->setLeftChild(nullptr);
            root->setRightChild(nullptr);
        // Rakennetaan puuta rekursiivisesti.
        } else {
            root->setLeftChild(splitTree(areas.first, level - 1));
            root->setRightChild(splitTree(areas.second, level - 1));
        }
    }
    return root;
}

// Funktio, joka jakaa osa-alueiden alueen pienempiin osiin.
std::pair<std::shared_ptr<AreaData>, std::shared_ptr<AreaData> >
    DungeonMap::splitArea(std::shared_ptr<AreaData> area)
{
    std::shared_ptr<AreaData> leftArea{nullptr};
    std::shared_ptr<AreaData> rightArea{nullptr};

    // Satunnaislukugeneraattorin avulla päätetään jakosuunta.
    int horizontal = rand() % 2;

    // Jaetaan alue pystysuoraan.
    if ( !horizontal ) {
        // Muodostetaan leveys, jonka vasen puolisko saa. Käytetään
        // apuna, kun lasketaan oikean puolen leveys.
        int newWidth{rand()% area->width_};

        leftArea = std::make_shared<AreaData>(
                    area->x_, area->y_, newWidth,
                    area->height_);

        rightArea = std::make_shared<AreaData>(
                    area->x_ + newWidth, area->y_,
                    area->width_ - newWidth, area->height_);
        // Käytetään leveys / korkeus suhdelukua apuna.
        if ( RATIO ) {
            // Oikean puolen suhdeluku
            double leftWRatio{double(leftArea->width_) /
                        double(leftArea->height_)};
            // Vasemman puolen suhdeluku
            double rightWRatio{double(rightArea->width_) /
                        double(rightArea->height_)};
            // Suhteista toinen ei ole sopiva.
            if ( leftWRatio < WRATIO || rightWRatio < WRATIO ) {
                // Yritetään jakaa aluetta uudestaan, jos sinne mahdtuu kaksi
                // pienempää aluetta.
                if ( area->width_ - MIN_WIDTH > MIN_WIDTH ) {
                    return splitArea(area);
                // Tehdään solmusta lehti, jossa on mahdollisesti isompi alue,
                // koska sitä ei pystynyt enää jakamaan.
                } else {
                    return std::make_pair(nullptr, nullptr);
                }
            }
        }
    // Jaetaan alue vaakasuoraan.
    } else {
        // Muodostetaan korkeus, jonka vasen puolisko saa. Käytetään
        // apuna, kun lasketaan oikean puolen korkeus.
        int newHeight{rand()% area->height_};
        leftArea = std::make_shared<AreaData>(
                    area->x_,area->y_, area->width_, newHeight);

        rightArea = std::make_shared<AreaData>(
                    area->x_, area->y_ + newHeight,
                    area->width_, area->height_ - newHeight);
        if ( RATIO ) {
            // Käytetään korkeus / leveys suhdetta apuna.
            double leftHRatio{double(leftArea->height_) /
                        double(leftArea->width_)};

            double rightHRatio{double(rightArea->height_) /
                        double(rightArea->width_)};

            if ( leftHRatio < HRATIO || rightHRatio < HRATIO ) {
                if ( area->height_ - MIN_HEIGHT > MIN_HEIGHT ) {
                    return splitArea(area);
                } else {
                    return std::make_pair(nullptr, nullptr);
                }
            }
        }
    }
    return std::make_pair(leftArea, rightArea);
}

// Funktio, joka hakee BSP-puurakenteesta lehtien tiedot ja muodostaa tietojen
// perusteella DungeonRoom-luokan instanssit.
void DungeonMap::createRooms() {
    std::deque<Tree *> leafs;
    treeRoot_->getLeafs(leafs);
    for ( auto data : leafs ) {
        rooms_.push_back(DungeonRoom{data->getData()});
    }
}

// Funktio, joka "kaivertaa" huoneet.
void DungeonMap::digRooms() {
    for ( auto room : rooms_ ) {
        int x{room.getX()+1};
        int y{room.getY()+1};
        int width{room.getWidth() - 2};
        int height{room.getHeight() - 2};
        for ( int posY = y; posY < y+height-1; ++posY ) {
            for ( int posX = x; posX < x + width-1; ++posX ) {
                tiles_.at(posX + posY*width_).code_ = 46;
                tiles_.at(posX + posY*width_).walkable_ = true;
            }
        }
    }
}

// Funktio, joka "kaivertaa" käytävät.
void DungeonMap::digCorridors(std::shared_ptr<Tree> root) {
    if ( root->isLeaf() ) {
        return;
    }
    int startX{root->getLeftChild()->getData()->centerX_};
    int startY{root->getLeftChild()->getData()->centerY_};
    int endX{root->getRightChild()->getData()->centerX_};
    int endY{root->getRightChild()->getData()->centerY_};
    dig(startX, startY, endX, endY);
    digCorridors(root->getLeftChild());
    digCorridors(root->getRightChild());
}

// Funktio, joka "kaivertaa" annetun alueen.
void DungeonMap::dig(int startX, int startY, int endX, int endY) {
    if ( endX < startX ) {
        int tmp = endX;
        endX = startX;
        startX = tmp;
    }
    if ( endY < startY ) {
        int tmp = endY;
        endY = startY;
        startY = tmp;
    }
    for ( int posY = startY; posY <= endY; ++posY ) {
        for ( int posX = startX; posX <= endX; ++posX ) {
            tiles_.at(posX + posY*width_).code_ = 46;
            tiles_.at(posX + posY*width_).walkable_ = true;
        }
    }
}

void DungeonMap::clearMap() {
    treeRoot_ = nullptr;
    rooms_.clear();
    tiles_ = std::vector<Tile>(width_*height_, Tile{});
}

bool DungeonMap::isInFov(int targetX, int targetY)
{
    return tiles_.at(targetX + width_*targetY).isInFov();
}

void DungeonMap::calculateFov(int playerX, int playerY, int radius)
{
    // it's const without the '&'
    for ( auto &tile : tiles_ ) {
        tile.setFov(false);
    }
    for ( int y = 0; y < height_; ++y ) {
        for ( int x = 0; x < width_; ++x ) {
            double dx = x - playerX;
            double dy = y - playerY;

            double distance = sqrt(dx*dx + dy*dy);
            if ( distance <= radius ) {
                // std::cout << "fov ja explored x["<< x << "] y[" << y << "]" << std::endl;
                tiles_.at(x + width_*y).setFov(true);
                tiles_.at(x + width_*y).setExplored(true);
            }
        }
    }
}

void DungeonMap::setProperties(int x, int y, bool isWalkable, bool isTransparent)
{
    tiles_.at(x + width_*y).setProperties(isWalkable, isTransparent);
}

bool DungeonMap::isWalkable(int targetX, int targetY)
{
    return tiles_.at(targetX + width_*targetY).isWalkable();
}

bool DungeonMap::isTransparent(int targetX, int targetY)
{
    return tiles_.at(targetX + width_*targetY).isTransparent();
}

bool DungeonMap::isExplored(int targetX, int targetY)
{
    if ( tiles_.at(targetX + width_*targetY).explored_ ) {
        return true;
    }
    return false;
}

Tile &DungeonMap::tileAt(int targetX, int targetY)
{
    return tiles_.at(targetX + width_*targetY);
}

std::deque<DungeonRoom> &DungeonMap::getRooms()
{
    return rooms_;
}

int DungeonMap::getSeed()
{
    return seed_;
}

std::pair<int, int> DungeonMap::getRandomLocation(unsigned int room)
{

}

} // GameWorld
