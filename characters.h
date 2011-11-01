#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "weapons.h"
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <iostream>
#include <vector>

class Player
{
public:
	SDL_Surface *screen_surface,*player_surface;
	SDL_Rect player_rect,screen_rect;
	Weapon* weapon;
	int number_of_weapons;
	std::vector<Weapon*> weapons;
	Uint32 color;
	Player(SDL_Surface * screen,int x, int y);
	~Player();
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	void move_to(int x, int y);
	void shoot();
	void equip_next();
	int ammo_count();
	void check_bounds();
	void draw();
};

class Enemy: public Player
{
public:
	Enemy(SDL_Surface *screen, int x, int y);
	~Enemy();
};

#endif
