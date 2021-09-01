#include "monsterbehaviour.hh"
#include "engine.hh"
#include "rmap.hh"

namespace GameWorld {


MonsterBehaviour::MonsterBehaviour()
{

}

void MonsterBehaviour::update(GameObject &gameObjectOwner)
{
    if ( gameObjectOwner.getEngine().isInFov(gameObjectOwner.getX(), gameObjectOwner.getY()) ) {
        // std::cout << "In fov of player!" << std::endl;
    }
}

bool MonsterBehaviour::moveOrAttack(GameObject &gameObjectOwner, int targetX, int targetY)
{

}
} // GameWorld
