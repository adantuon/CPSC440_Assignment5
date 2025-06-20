//Aiden D'Antuono

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include "SpriteSheet.h"
#include "Projectile.h"
#include "mappy_A5.h"

int main() {
	const int WIDTH = 512;
	const int HEIGHT = 512;
	bool keys[] = { false, false, false, false, false };
	int special = 0;
	int spawnedEnemies = 6;
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	bool exit = false;
	bool render = false;
	Sprite player;
	Sprite enemies[10];
	const int numPlayerProjectiles = 10;
	const int numEnemyProjectiles = 40;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//program init
	if (!al_init()) {
		return -1;
	}

	display = al_create_display(WIDTH, HEIGHT);

	if (!display) {
		return -1;
	}

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_font("PressStart2P.ttf", 48, 0);
	ALLEGRO_FONT *smallFont = al_load_font("PressStart2P.ttf", 16, 0);

	Projectile playerProjectiles[numPlayerProjectiles];
	Projectile enemyProjectiles[numEnemyProjectiles];

	player.InitSprites((char *)"Player.png", 32, 240, true, playerProjectiles, numPlayerProjectiles);
	
	enemies[0].InitSprites((char *)"Enemy.png", 352, 240, false, enemyProjectiles, numEnemyProjectiles);
	enemies[1].InitSprites((char *)"Enemy.png", 608, 240, false, enemyProjectiles, numEnemyProjectiles);
	enemies[2].InitSprites((char *)"Enemy.png", 832, 240, false, enemyProjectiles, numEnemyProjectiles);
	enemies[3].InitSprites((char *)"Enemy.png", 992, 112, false, enemyProjectiles, numEnemyProjectiles);
	enemies[4].InitSprites((char *)"Enemy.png", 1184, 240, false, enemyProjectiles, numEnemyProjectiles);
	enemies[5].InitSprites((char *)"Enemy.png", 1400, 240, false, enemyProjectiles, numEnemyProjectiles);
	enemies[6].InitSprites((char *)"Enemy.png", 0, 0, false, enemyProjectiles, numEnemyProjectiles);
	enemies[7].InitSprites((char *)"Enemy.png", 0, 0, false, enemyProjectiles, numEnemyProjectiles);
	enemies[8].InitSprites((char *)"Enemy.png", 0, 0, false, enemyProjectiles, numEnemyProjectiles);
	enemies[9].InitSprites((char *)"Enemy.png", 0, 0, false, enemyProjectiles, numEnemyProjectiles);


	for (int i = 0; i < 10; i++) {
		playerProjectiles[i].initProjectile(false);
	}
	for (int i = 0; i < 40; i++) {
		enemyProjectiles[i].initProjectile(true);
	}


	int xOff = 0;
	int yOff = 0;

	
	char mapName[16] = "Level0.FMP";
	if (MapLoad(mapName, 1)) {
		return -5;
	}
	

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));

	al_start_timer(timer);

	al_set_target_bitmap(al_get_backbuffer(display));
	//draw the background tiles
	MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

	//draw foreground tiles
	MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
	player.DrawSprites(0, 0);
	for (int i = 0; i < 10; i++) {
		enemies[i].DrawSprites(0, 0);
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	while (!exit) {

		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			render = true;

			for (int i = 0; i < numPlayerProjectiles; i++) {
				playerProjectiles[i].UpdateProjectile(mapwidth * 32, mapheight * 32);
			}

			for (int i = 0; i < numEnemyProjectiles; i++) {
				enemyProjectiles[i].UpdateProjectile(mapwidth * 32, mapheight * 32);
			}

			if (keys[SPACE]) {
				player.UpdateSprites(enemies, spawnedEnemies, SPACE, mapwidth * 32, mapheight * 32);
			}
			else if (keys[UP]) {
				player.UpdateSprites(enemies, spawnedEnemies, UP, mapwidth * 32, mapheight * 32);
			}
			else if (keys[DOWN]) {
				player.UpdateSprites(enemies, spawnedEnemies, DOWN, mapwidth * 32, mapheight * 32);
			}
			else if (keys[LEFT]) {
				player.UpdateSprites(enemies, spawnedEnemies, LEFT, mapwidth * 32, mapheight * 32);
			}
			else if (keys[RIGHT]) {
				player.UpdateSprites(enemies, spawnedEnemies, RIGHT, mapwidth * 32, mapheight * 32);
			}
			else {
				player.UpdateSprites(enemies, spawnedEnemies, -1, mapwidth * 32, mapheight * 32);
			}

			special = player.CollisionSpecial();

			for (int i = 0; i < spawnedEnemies; i++) {
				enemies[i].UpdateSpritesAI(player, mapwidth * 32, mapheight * 32);
			}
		}

		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = true;
		}

		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				exit = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				exit = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if (special != 0) {
			if (special == 1) {
				MapChangeLayer(1);
			}
			else if (special == 2) {
				//change map
				MapChangeLayer(2);

				//move player
				player.setX(0);

				//respawn enemies
				for (int i = 0; i < spawnedEnemies; i++) {
					enemies[i].setLives(1);
				}

				spawnedEnemies = 10;

				enemies[0].setX(800);
				enemies[0].setY(32);
				enemies[1].setX(832);
				enemies[1].setY(64);
				enemies[2].setX(864);
				enemies[2].setY(96);
				enemies[3].setX(896);
				enemies[3].setY(128);
				enemies[4].setX(1280);
				enemies[4].setY(128);
				enemies[5].setX(1248);
				enemies[5].setY(128);
				enemies[6].setX(1216);
				enemies[6].setY(128);
				enemies[7].setX(1184);
				enemies[7].setY(128);
				enemies[8].setX(1120);
				enemies[8].setY(128);
				enemies[9].setX(1056);
				enemies[9].setY(128);
			}
		}

		if (render && al_is_event_queue_empty(eventQueue)) {
			render = false;

			xOff = player.getX() + player.getWidth() - WIDTH / 2;
			yOff = player.getY() + player.getHeight() - HEIGHT / 2;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0)
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT))
				yOff = mapheight * mapblockheight - HEIGHT;

			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);

			player.DrawSprites(xOff, yOff);

			for (int i = 0; i < spawnedEnemies; i++) {
				enemies[i].DrawSprites(xOff, yOff);
			}

			for (int i = 0; i < numPlayerProjectiles; i++) {
				playerProjectiles[i].DrawProjectile(xOff, yOff);
			}

			for (int i = 0; i < numEnemyProjectiles; i++) {
				enemyProjectiles[i].DrawProjectile(xOff, yOff);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	MapFreeMem();
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);

	return 0;
}

int collided(int x, int y) {
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return blockdata->tl;
}

int specialValue(int x, int y)
{

	BLKSTR *data;
	data = MapGetBlock(x / mapblockwidth, y / mapblockheight);

	return data->user1;
}
