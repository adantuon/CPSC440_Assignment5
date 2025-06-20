#pragma once
#include <allegro5/allegro.h>

int collided(int x, int y);

class Projectile {
public:
	Projectile();
	~Projectile();
	void initProjectile(bool enemy);
	void DrawProjectile(int xoffset, int yoffset);
	void FireProjectile(int x, int y, int direction);
	void UpdateProjectile(int width, int height);
	bool getLive() { return live; }
private:
	int x;
	int y;
	int frameWidth;
	int frameHeight;
	bool live;
	int speed;
	int direction;

	ALLEGRO_BITMAP *image;
};