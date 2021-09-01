#include "rgameobjectfactory.hh"
#include "attackablecomponent.hh"
#include "monsterbehaviour.hh"
#include "bodycomponent.hh"
#include "containercomponent.hh"
#include "destroyablecomponent.hh"
#include "pickupcomponent.hh"
#include "gameobject.hh"

namespace GameWorld {

RGameObjectFactory::RGameObjectFactory() : data_{nullptr}
{

}

GameObject RGameObjectFactory::createMonster(Data::MonsterTypes type)
{
    // int typeCount{static_cast<int>(Data::MonsterTypes::TYPE_MAX)};
    std::string monsterType{Data::mTypeS(type)};
    int monsterCount{static_cast<int>(data_->getMonsterData().at(monsterType).size())};
    int monster{rand() % monsterCount};

    Monster newM{data_->getMonsterData().at(monsterType).at(monster)};
    GameObjectTypes newT{data_->getObjectTypeData().at(monsterType)};
    GameObject newOBJ{GameObject(0, 0, newM.character_.at(0), newM.name_, newM.color_)};

    if ( newT.attackable_ ) {
        std::cout << "Attackable, ";
    }
    // Movement
    if ( newT.behaviour_ ) {
        std::cout << "Behaviour, ";
        newOBJ.setMovement(std::make_shared<MonsterBehaviour>());
    }
    if ( newT.body_ ) {
        std::cout << "Body, ";
    }
    if ( newT.container_ ) {
        std::cout << "Container, ";
    }
    if ( newT.destroyable_ ) {
        std::cout << "Destroyable, ";
    }
    if ( newT.pickup_ ) {
        std::cout << "Pickup.";
    }

    return newOBJ;

}

GameObject RGameObjectFactory::createItem()
{

}

void RGameObjectFactory::setData(std::shared_ptr<DataLoader> data)
{
    data_ = data;
}

} // GameWorld
