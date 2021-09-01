#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH
#include <memory>
#include <string>
#include "BearLibTerminal.h"
#include "playerbehaviour.hh"
#include "attackablecomponent.hh"
#include "destroyablecomponent.hh"
#include "pickupcomponent.hh"
#include "containercomponent.hh"
#include "bodycomponent.hh"
#include "engine.hh"

namespace GameWorld {

class Engine;
class BehaviourComponent;
class AttackableComponent;
class DestroyableComponent;
class PickupComponent;

class GameObject
{
    public:
        GameObject();
        GameObject(int x, int y, int code, std::string name, std::string color);

        ~GameObject();

        void render();

        void update();
        void killGameObject(int code, std::string corpseName, bool blocks,
                            std::string color = "red");
        int getX() const;
        int getY() const;
        std::string getName() const;
        Engine &getEngine();

        void setLocation(int targetX, int targetY);
        void setMovement(std::shared_ptr<BehaviourComponent> comp);
        void setAttackable(std::shared_ptr<AttackableComponent> comp);
        void setDestroyable(std::shared_ptr<DestroyableComponent> comp);
        void setPickable(std::shared_ptr<PickupComponent> comp);
        void setContainer(std::shared_ptr<ContainerComponent> comp);
        void setBody(std::shared_ptr<BodyComponent> comp);
        void setEngine(Engine *engine);

    private:
        int x_;
        int y_;
        int code_;
        std::string name_;
        std::string color_;
        bool blocks_;
        // Engine *engine_;
        std::shared_ptr<Engine> engine_;
        std::shared_ptr<AttackableComponent> attackable_;
        std::shared_ptr<BehaviourComponent> movement_;
        std::shared_ptr<DestroyableComponent> destroyable_;
        std::shared_ptr<PickupComponent> pickup_;
        std::shared_ptr<ContainerComponent> container_;
        std::shared_ptr<BodyComponent> body_;
};
} // GameWorld
#endif // GAMEOBJECT_HH
