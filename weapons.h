/*
 *  weapons.h
 *  Shooter
 *
 *  Created by David Albornoz on 10/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef WEAPONS_H
#define WEAPONS_H

#include <SDL/SDL.h>
#include <vector>
class Pistol
{
	std::vector<SDL_Rect> bullets;
	SDL_Surface *screen_surface;
	SDL_Rect screen_rect;
	Uint32 color;
public:
	Pistol(SDL_Surface *screen);
	~Pistol();
	int how_many_bullets();
	void shoot(int x, int y);
	void draw();
};
#endif