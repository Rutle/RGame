#include "BearLibTerminal.h"
#include "rgame.hh"

int main(/* int argc, char *argv[]*/)
{
    RGame *game = new RGame(80, 40);
    // true = just display map
    // false = start from the beginning
    return game->run(false);
    // return game->initGame();
}

