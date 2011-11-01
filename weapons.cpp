#include "weapons.h"

Weapon::Weapon(SDL_Surface *screen)
{
	screen_surface = screen;
	screen_rect = screen->clip_rect;
}
Weapon::~Weapon()
{
	SDL_FreeSurface(bullet_surface);
}
void Weapon::draw()
{
	for(int i=0;i<bullets.size();i++)
	{
		//SDL_FillRect(screen_surface, &bullets[i], 0xffffffff);
		SDL_BlitSurface(bullet_surface,NULL,screen_surface,&bullets[i].bullet);
		bullets[i].bullet.x += 10;
		if(bullets[i].bullet.x > screen_rect.w)
		{
			i -= 1; // erasing will move the contents ahead of i back, so move i back by 1
			bullets.erase(bullets.begin()+i);
		}
	}
}
void Weapon::shoot(int x, int y){}
int Weapon::how_many_bullets(){return 0;}
Pistol::Pistol(SDL_Surface *screen): Weapon(screen)
{
	bullet_surface = IMG_Load("pistol.png");
}
Pistol::~Pistol()
{
	//nothing
}
int Pistol::how_many_bullets()
{
	return (int)bullets.size();
}
void Pistol::shoot(int x, int y)
{
	// create a bullet and position it
	SDL_Rect bullet_rect = {x,y,50,24};
	Bullet bullet = {bullet_rect,x};
	if(bullets.size() >= 1)
	{
		Bullet current_bullet = bullets.back();
		if(current_bullet.bullet.x > current_bullet.start_x+64)
		{
			bullets.push_back(bullet);
		}
	}
	else
	{
		bullets.push_back(bullet);
	}
}
Beam::Beam(SDL_Surface *screen): Weapon(screen)
{
	bullet_surface = IMG_Load("beam.png");
}
Beam::~Beam(){}
void Beam::shoot(int x, int y)
{
	// first create a referenct rect
	SDL_Rect b_rect = {x,y,16,64};
	Bullet bullet = {b_rect,x};
	bullets.push_back(bullet);
}
int Beam::how_many_bullets()
{
	return (int)(bool)bullets.size();
}