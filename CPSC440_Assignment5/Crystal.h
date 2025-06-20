//Aiden D'Antuono

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Projectile.h"
#include "mappy_A5.h"

class Crystal {
public:
	Crystal();
	~Crystal();
	void InitCrystal(char file[16], int x, int y, Projectile *projectiles, int numProjectiles);
	void UpdateCrystal();
	void DrawCrystal(int xoffset, int yoffset);
	float getX() { return x; }
	void setX(int inX) { x = inX; }
	float getY() { return y; }
	void setY(int inY) { y = inY; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	int getLives() { return lives; }
	void setLives(int value) { lives = value; }
	bool returnInPlay() { return inPlay; }

private:
	bool inPlay;
	float x;
	float y;
	int maxFrame;
	int curFrame;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int lives;
	Projectile *projectiles;
	int numProjectiles;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sample;
};