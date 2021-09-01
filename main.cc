#include "BearLibTerminal.h"
#include "rgame.hh"

int main(int argc, char *argv[])
{
    RGame *game = new RGame(80, 40);
    return game->run(true);
}

