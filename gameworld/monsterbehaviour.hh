#ifndef MONSTERBEHAVIOUR_HH
#define MONSTERBEHAVIOUR_HH
#include "behaviourcomponent.hh"

namespace GameWorld {
class GameObject;
class MonsterBehaviour : public BehaviourComponent
{
    public:
        MonsterBehaviour();
        void update(GameObject &gameObjectOwner);
    private:
        bool moveOrAttack(GameObject &gameObjectOwner,
                          int targetX, int targetY);

};
}
#endif // MONSTERBEHAVIOUR_HH
