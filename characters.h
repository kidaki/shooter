/*
 *  characters.h
 *  Shooter
 *
 *  Created by David Albornoz on 10/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <weapons.h>

class Player
{
	SDL_Surface *screen_surface;
	SDL_Rect player_rect,screen_rect;
	Pistol *pistol;
	Uint32 color;
public:
	Player(SDL_Surface * screen,int x, int y);
	~Player();
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	void move_to(int x, int y);
	void shoot();
	int ammo_count();
	void check_bounds();
	void draw();
};

//class Enemy

#endif