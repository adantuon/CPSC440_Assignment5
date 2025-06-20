//Aiden D'Antuono

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int collided(int x, int y);

class Sprite {
	public:
		Sprite();
		~Sprite();
		void InitSprites();
		bool UpdateSprites(int dir, int width, int height); //dir 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
		void DrawSprites(int xoffset, int yoffset);
		float getX() { return x; }
		void setX(int inX) { x = inX; }
		float getY() { return y; }
		void setY(int inY) { y = inY; }
		int getWidth() { return frameWidth; }
		int getHeight() { return frameHeight; }

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

		ALLEGRO_BITMAP *image;
};