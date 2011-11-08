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
	float time_running;
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
class Level
{
public:
	typedef struct level_enemy {
		Enemy *enemy;
		float time;
	};
	std::vector<level_enemy> level_enemies;
	int number,enemy_number;
	int enemy_count;
	float time_passed;
	SDL_Surface *screen;
	Level(int num,SDL_Surface *screen);
	~Level();
	void virtual init() = 0;
	
};
class Level1:public Level
{
public:
	Level1(SDL_Surface *screen);
	void init();
};
#endif
