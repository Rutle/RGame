#ifndef BEHAVIOURCOMPONENT_HH
#define BEHAVIOURCOMPONENT_HH

// #include "gameobject.hh"

namespace GameWorld {

class GameObject;

// Component for Behaviour such as movement and attack of a gameobject (player
// or enemy).
class BehaviourComponent {
    public:
        BehaviourComponent() = default;
        virtual ~BehaviourComponent() = default;
        virtual void update(GameObject &gameObjectOwner) = 0;

};
} // GameWorld
#endif // BEHAVIOURCOMPONENT_HH
