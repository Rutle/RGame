#include "gameobject.hh"
const int HOFFSET = 1;
const int WOFFSET = 1;

namespace GameWorld {

GameObject::GameObject() : x_{0}, y_{0}, code_{'@'}, name_{"None"},
    color_{"red"}, blocks_{true}, engine_{nullptr}, attackable_{nullptr},
    movement_{nullptr}, destroyable_{nullptr}, pickup_{nullptr},
    container_{nullptr}, body_{nullptr}
{
    std::cout << "Default Constructor of GameObject" << std::endl;
}

GameObject::GameObject(int x, int y, int code, std::string name,
                       std::string color) :
    x_{x}, y_{y}, code_{code}, name_{name}, color_{color}, blocks_{false},
    attackable_{nullptr}, movement_{nullptr}, destroyable_{nullptr},
    pickup_{nullptr}, container_{nullptr}, body_{nullptr}
{

}

GameObject::~GameObject()
{
    // delete engine_;
}

void GameObject::render()
{
    terminal_color(color_.c_str());
    terminal_put(x_ + WOFFSET, y_ + HOFFSET, code_);
}

void GameObject::update()
{
    if ( movement_ != nullptr ) {
        movement_->update(*this);
    }
}

int GameObject::getX() const
{
    return x_;
}

int GameObject::getY() const
{
    return y_;
}

void GameObject::setLocation(int targetX, int targetY)
{
    try {
        x_ = targetX;
        y_ = targetY;
    } catch ( const char* msg ) {
        std::cerr << msg << std::endl;
        x_ = 20;
        y_ = 20;
    }

}

void GameObject::setMovement(std::shared_ptr<BehaviourComponent> comp)
{
    movement_ = comp;
}

void GameObject::setEngine(Engine *engine)
{
    /*
    try {
        engine_ = engine;
    } catch ( const char* msg ) {
        std::cerr << msg << std::endl;
        engine_ = nullptr;
    }
    */
    engine_ = std::shared_ptr<Engine>(engine);
}

std::string GameObject::getName() const
{
    return name_;
}

Engine &GameObject::getEngine()
{
    return *engine_;
}
} // GameWorld
