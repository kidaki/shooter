#ifndef WEAPONS_H
#define WEAPONS_H

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <vector>
#include <iostream>

typedef struct{
	SDL_Rect bullet;
	int start_x;
} Bullet;

class Weapon
{
public:
	SDL_Surface *screen_surface,*bullet_surface;
	SDL_Rect screen_rect;
	std::vector<Bullet> bullets;
	bool equiped;
	Weapon(SDL_Surface *screen);
	~Weapon();
	virtual void shoot(int x, int y);
	virtual int how_many_bullets();
	void draw();
};
	
class Pistol: public Weapon
{
public:
	Pistol(SDL_Surface *screen);
	~Pistol();
	void shoot(int x, int y);
	int how_many_bullets();
};
class Beam: public Weapon
{
public:
	Beam(SDL_Surface *screen);
	~Beam();
	void shoot(int x, int y);
	int how_many_bullets();
};
#endif
