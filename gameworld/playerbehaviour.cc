#include "playerbehaviour.hh"
#include "engine.hh"
#include "rmap.hh"

namespace GameWorld {

PlayerBehaviour::PlayerBehaviour()
{

}

void PlayerBehaviour::update(GameObject &gameObjectOwner)
{
    int key{terminal_read()};

    int dx{0};
    int dy{0};

    switch(key) {
        case TK_UP : dy=-1; break;
        case TK_DOWN : dy=1; break;
        case TK_LEFT : dx=-1; break;
        case TK_RIGHT : dx=1; break;
        case TK_CLOSE : std::cout << "CLOSE" << std::endl;
            gameObjectOwner.getEngine().setGameState(Engine::EXIT_GAME);
            break;
        default:
            handleKey(gameObjectOwner, key);
            break;
    }
    // Moved one step to a direction. Checking if moving or attacking.
    if (dx != 0 || dy != 0) {
        // New turn only when moved so perhaps moving to wall doesn't change turn.


        if (moveOrAttack(gameObjectOwner, gameObjectOwner.getX() + dx,
                         gameObjectOwner.getY() + dy)) {
            gameObjectOwner.getEngine().setGameStatus(Engine::NEW_TURN);
            // Calculate fov!
            gameObjectOwner.getEngine().computeFov();
            std::cout << "NEW TURN" << std::endl;
        }
    }
}

bool PlayerBehaviour::moveOrAttack(GameObject &gameObjectOwner,
                                           int targetX, int targetY)
{
    if ( targetX < 0 || targetY < 0 ) {
        // Until I make map to have walls around
        return false;
    }
    // Check if a wall
    if ( gameObjectOwner.getEngine().getMap()->isWall(targetX, targetY) ) {
        std::cout << "Move failed <WALL> x:[" << targetX << "] y:[" << targetY << "]" << std::endl;
        std::cout << "Player x:[" << gameObjectOwner.getX() << "] y:[" << gameObjectOwner.getY() << "]" << std::endl;
        return false;
    }

    // Check if gameobjects that block (enemies)
    for ( auto obj = gameObjectOwner.getEngine().getGameObjects().begin();
          obj != gameObjectOwner.getEngine().getGameObjects().end(); ++obj ) {
        if ( (*obj)->getX() == targetX && (*obj)->getY() == targetY ) {
            std::cout << "Attempting to move over: " << (*obj)->getName() << std::endl;
            return false;
        }
    }

    // Move player
    gameObjectOwner.setLocation(targetX, targetY);
    return true;
}

void PlayerBehaviour::handleKey(GameObject &gameObjectOwner, int key)
{
    std::cout << "Pressed key [" << key << "]" << std::endl;
}
} // GameWorld
