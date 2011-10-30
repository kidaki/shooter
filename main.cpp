#include "game.h"

int main(int argc, char** argv)
{
    Game *game = new Game();
    game->loop();
    return 0;
}
