#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "weapons.h"
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <iostream>
#include <vector>

class Character
{
public:
	SDL_Surface *screen_surface,*character_surface;
	SDL_Rect character_rect,screen_rect;
	Character(SDL_Surface *screen,const char* image_file);
	~Character();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void move_to(int x, int y);
	virtual void draw();
};
class Player : public Character
{
public:
	Weapon* weapon;
	int number_of_weapons;
	std::vector<Weapon*> weapons;
	Player(SDL_Surface * screen,const char* image_file);
	~Player();
	void shoot();
	void equip_next();
	int ammo_count();
	void check_bounds();
	void draw();
};

class Enemy: public Character
{
public:
	Enemy(SDL_Surface *screen,const char* image_file);
	~Enemy();
	void draw();
};

#endif
