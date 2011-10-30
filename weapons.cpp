/*
 *  weapons.cpp
 *  Shooter
 *
 *  Created by David Albornoz on 10/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "weapons.h"

Pistol::Pistol(SDL_Surface *screen)
{
	this->screen_surface = screen;
	SDL_GetClipRect(screen_surface, &screen_rect);
	color = SDL_MapRGB(screen_surface->format, 0xff, 0xff, 0xff);
}
Pistol::~Pistol()
{
	//destructor, nothing yet
}
int Pistol::how_many_bullets()
{
	return (int)bullets.size();
}
void Pistol::shoot(int x, int y)
{
	// create a bullet and position it
	SDL_Rect bullet = {x,y,10,10};
	bullets.push_back(bullet);
}
void Pistol::draw()
{
	for(int i=0;i<bullets.size();i++)
	{
		SDL_FillRect(screen_surface, &bullets[i], color);
		bullets[i].x += 10;
		if(bullets[i].x > screen_rect.w)
		{
			i -= 1; // erasing will move the contents ahead of i back, so move i back by 1
			bullets.erase(bullets.begin()+i);
		}
	}
}