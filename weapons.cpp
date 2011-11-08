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
		bullets[i].bullet.x += 5 * bullets[i].direction;
		if(bullets[i].angle != 0)
		{
			bullets[i].bullet.y +=1*bullets[i].angle;
		}
		if(bullets[i].bullet.x > screen_rect.w or bullets[i].bullet.x < 0)
		{
			bullets.erase(bullets.begin()+i);
			i -= 1; // erasing will move the contents ahead of i back, so move i back by 1
		}
	}
}
//void Weapon::shoot(int x, int y){}
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
void Pistol::shoot(int x, int y, int x_dir)
{
	// create a bullet and position it
	SDL_Rect bullet_rect = {x,y,50,24};
	Bullet bullet = {bullet_rect,x,x_dir,0};
	if(bullets.size() >= 1)
	{
		//Bullet current_bullet = bullets.back();
		if(bullets.back().bullet.x > bullets.back().start_x+64*bullets.back().direction)
		{
			bullets.push_back(bullet);
		}
	}
	else
	{
		bullets.push_back(bullet);
	}
}

TriPistol::TriPistol(SDL_Surface *screen):Weapon(screen)
{
	bullet_surface = IMG_Load("tripistol.png");
}
void TriPistol::shoot(int x, int y, int x_dir)
{
	SDL_Rect bullet_rect = {x,y,26,26};
	Bullet bullet1 = {bullet_rect,x,x_dir,1};
	Bullet bullet2 = {bullet_rect,x,x_dir,0};
	Bullet bullet3 = {bullet_rect,x,x_dir,-1};
	if(bullets.size() >= 1)
	{
		if(abs(bullets.back().bullet.x - bullets.back().start_x) >= 52)
		{
			bullets.push_back(bullet1);
			bullets.push_back(bullet2);
			bullets.push_back(bullet3);
		}
	}
	else
	{
		bullets.push_back(bullet1);
		bullets.push_back(bullet2);
		bullets.push_back(bullet3);
	}
}
int TriPistol::how_many_bullets()
{
	return bullets.size();
}
Beam::Beam(SDL_Surface *screen): Weapon(screen)
{
	bullet_surface = IMG_Load("beam.png");
}
Beam::~Beam(){}
void Beam::shoot(int x, int y, int x_vel)
{
	// first create a referenct rect
	SDL_Rect b_rect = {x,y,16,64};
	Bullet bullet = {b_rect,x,x_vel,0};
	bullets.push_back(bullet);
}
int Beam::how_many_bullets()
{
	return (int)(bool)bullets.size();
}