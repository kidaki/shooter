#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include "characters.h"
class Game
{
    SDL_Surface *screen, *text;
    SDL_Event event;
    bool running;
    Uint32 start;
    int FPS;
    bool movement[4];
	bool shooting;
    Player *player;
    TTF_Font *font;
    SDL_Color font_color;
    std::string log;
    std::stringstream tmp;

    public:
    Game();
    ~Game();
    void handle_event();
    void loop();
};
#endif
