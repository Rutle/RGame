#ifndef RGAMEOBJECTFACTORY_HH
#define RGAMEOBJECTFACTORY_HH
#include <memory>
#include <iostream>
#include <map>
#include "dataloader.hh"
#include "rdata.hh"

namespace GameWorld {

class GameObject;
class RGameObjectFactory
{
    public:
        RGameObjectFactory();
        GameObject createMonster(Data::MonsterTypes type);
        GameObject createItem();
        void setData(std::shared_ptr<DataLoader> data);
    private:
        std::shared_ptr<DataLoader> data_;
        std::map<std::string, int> stats_;

};
} // GameWorld
#endif // RGAMEOBJECTFACTORY_HH
