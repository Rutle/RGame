#ifndef ATTACKABLECOMPONENT_HH
#define ATTACKABLECOMPONENT_HH
#include "gameobject.hh"
namespace GameWorld {
class AttackableComponent {
    public:
        AttackableComponent() = default;
        virtual ~AttackableComponent() = default;
    private:
};
} // GameWorld
#endif // ATTACKABLECOMPONENT_HH
