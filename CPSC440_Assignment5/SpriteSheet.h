//Aiden D'Antuono

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Projectile.h"
#include "Crystal.h"
#include "mappy_A5.h"

int collided(int x, int y);
int specialValue(int x, int y);

class Sprite {
	public:
		Sprite();
		~Sprite();
		void InitSprites(char file[16], int x, int y, bool player, Projectile *projectilesP, int numProjectilesP, Projectile *projectilesE, int numProjectilesE, Crystal *crystal);
		void UpdateSprites(Sprite *enemies, int numEnemies, int dir, int width, int height); //dir 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT, 4 = firing
		void UpdateSpritesAI(Sprite &player, int width, int height);
		int CollisionSpecial();
		void DrawSprites(int xoffset, int yoffset);
		float getX() { return x; }
		void setX(int inX) { x = inX; }
		float getY() { return y; }
		void setY(int inY) { y = inY; }
		int getWidth() { return frameWidth; }
		int getHeight() { return frameHeight; }
		int getLives() { return lives; }
		void setLives(int value) { lives = value; }

	private:
		float x;
		float y;
		int maxFrame;
		int curFrame;
		int frameCount;
		int frameDelay;
		int frameWidth;
		int frameHeight;
		int animationColumns;
		int direction;
		int speed;
		bool firing;
		int lives;
		int directionAI;
		Projectile *projectilesP;
		int numProjectilesP;
		Projectile *projectilesE;
		int numProjectilesE;
		Crystal *crystal;

		ALLEGRO_BITMAP *image;
		ALLEGRO_SAMPLE *sample;
};