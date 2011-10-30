/*
 *  characters.cpp
 *  Shooter
 *
 *  Created by David Albornoz on 10/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "characters.h"

Player::Player(SDL_Surface *screen,int x, int y)
{
	this->screen_surface = screen;
	SDL_GetClipRect(screen, &screen_rect);
	pistol = new Pistol(screen);
	color = SDL_MapRGB(screen->format, 0x33, 0x66, 0x33);
	player_rect.x = x;
	player_rect.y = y;
	player_rect.w = 50;
	player_rect.h = 50;
}
Player::~Player()
{
	delete pistol;
}
void Player::move_up()
{
	player_rect.y -= 10;
}
void Player::move_down()
{
	player_rect.y += 10;
}
void Player::move_right()
{
	player_rect.x += 10;
}
void Player::move_left()
{
	player_rect.x -= 10;
}
void Player::move_to(int x, int y)
{
	player_rect.x = x;
	player_rect.y = y;
}
void Player::shoot()
{
	pistol->shoot(player_rect.x,player_rect.y);
}
int Player::ammo_count()
{
	return pistol->how_many_bullets();
}
void Player::check_bounds()
{
	// check if player if above or below screen
	if(player_rect.y < 0)
	{
		player_rect.y = 0;
	}
	else if(player_rect.y+player_rect.h > screen_rect.h)
	{
		player_rect.y = screen_rect.h - player_rect.h;
	}
	//check if player is left of right of screen 
	if(player_rect.x + player_rect.w > screen_rect.w)
	{
		player_rect.x = screen_rect.w - player_rect.w;
	}
	else if(player_rect.x < 0)
	{
		player_rect.x = 0;
	}
}
void Player::draw()
{
	check_bounds();
	SDL_FillRect(screen_surface, &player_rect, color);
	pistol->draw();
}
