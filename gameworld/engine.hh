#ifndef ENGINE_HH
#define ENGINE_HH
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "BearLibTerminal.h"
#include "gameobject.hh"
#include "rgameobjectfactory.hh"
#include "rworldgenerator.hh"

namespace GameWorld {
class DungeonMap;
class RWorldGenerator;
class GameObject;
class RMap;
class Engine
{
    public:
        // Muuta "GameTurnState".
        enum GameStatus {
            STARTUP,            // first frame of the game
            IDLE,               // no new turn. Redraw the same screen.
            NEW_TURN,           // update the monsters position
            VICTORY,            // the player won
            DEFEAT,             // the player was killed

        };
        enum GameState {
            EXIT_GAME = 0,      // Exit game
            STAY = 1            // Stay in game
        };
        Engine();
        Engine(int width, int height);
        void checkInput();
        void update();
        void render();
        void run();
        bool initEngine();

        void setGameStatus(GameStatus newGameStatus);
        void setGameState(GameState newGameState);
        void moveObjectToFront(std::shared_ptr<GameObject> gameObject);
        std::list<std::shared_ptr<GameObject>>& getGameObjects();
        GameStatus getGameStatus() const;
        std::shared_ptr<RMap> &getMap();
        void setMapSize(int width, int height);
        std::shared_ptr<GameObject> &getPlayer();

        bool isInFov(int targetX, int targetY);
        void computeFov();
    private:
        void changeMap();
        void drawFrame(int x, int y, int w, int h);
        int key_;

        //std::list<std::shared_ptr<GameObject>> gameObjects_;
        std::shared_ptr<GameObject> player_;
        GameStatus gameStatus_;
        GameState gameState_;
        std::shared_ptr<RMap> map_;
        int width_;
        int height_;
        int mapWidth_;
        int mapHeight_;
        std::unique_ptr<RWorldGenerator> generator_;
        // std::map<int, std::list<std::shared_ptr<GameObject>>> generatedData_;
        std::map<int, std::list<std::shared_ptr<GameObject>>> generatedData_;


};
} // GameWorld

#endif // ENGINE_HH
