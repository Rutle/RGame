#ifndef PLAYERBEHAVIOUR_HH
#define PLAYERBEHAVIOUR_HH
#include "behaviourcomponent.hh"

namespace GameWorld {

class GameObject;
class PlayerBehaviour : public BehaviourComponent
{
    public:
        PlayerBehaviour();
        void update(GameObject &gameObjectOwner);

    private:
        bool moveOrAttack(GameObject &gameObjectOwner,
                          int targetX, int targetY);
        void handleKey(GameObject &gameObjectOwner, int key);
};
} // GameWorld
#endif // PLAYERBEHAVIOUR_HH
