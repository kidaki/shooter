#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "characters.h"
class Game
{
    SDL_Surface *screen, *text;
    SDL_Event event;
    bool running;
	bool game_over;
	int time_running;
    float start;
    int FPS;
    bool movement[4];
	bool shooting;
    Player *player;
	std::vector<Enemy*> enemies;
    TTF_Font *font;
    SDL_Color font_color;
    std::string log;
    std::stringstream tmp;

    public:
    Game();
    ~Game();
    void handle_event();
	bool check_collisions(SDL_Rect rect1, SDL_Rect rect2);
    void loop();
};
#endif
