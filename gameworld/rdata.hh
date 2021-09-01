#ifndef RDATA_HH
#define RDATA_HH
#include <iostream>
#include <map>
namespace Data {
enum class GameTurnState : int {
    STARTUP = 0,        // first frame of the game
    IDLE,               // no new turn. Redraw the same screen.
    NEW_TURN,           // update the monsters position
    VICTORY,            // the player won
    DEFEAT,             // the player was killed

};
/*
enum GameState {
    EXIT_GAME = 0,      // Exit game
    STAY = 1            // Stay in game
};
*/
enum class MonsterTypes : int {
    BEAST = 0,
    DRAGON = 1,
    ELEMENTAL = 2,
    HUMANOID = 3,
    UNDEAD = 4,
    DEMON = 5,
    TYPE_MAX = 6
};

std::string mTypeS(MonsterTypes type);

enum class Races : int {
    HUMAN = 0,           // Human race
    TROLL,
    ORC,
    GNOME,
    ELF,

};
} // Data
#endif // RDATA_HH
