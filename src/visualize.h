# include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>	
# include <graphics.h>
# include <time.h>
# include <conio.h>
# include <windows.h>
# include "uno_logic.h"

#ifndef MAX_PLAYERS
#define MAX_PLAYERS 7
#endif

#ifndef MAX_CARDS
#define MAX_CARDS 108
#endif

#ifndef _VISUALIZE_H_
#define _VISUALIZE_H_

typedef struct {
	IMAGE image_card;
	int card_id;
} Card_image;

extern Card_image 
card_images[MAX_CARDS];

typedef struct {
	IMAGE image_player;
	int player_id;
} Player_image;

extern Player_image player_images[MAX_PLAYERS];

typedef struct {
	int color_card_id;
	IMAGE image_color;
} Color_card_image;

extern Color_card_image color_card_images[5];
int initialize_startgame();

void initialize_card_image();

void initialize_player_image();

void initialize_color_card_image();

int select_color_visualize();

void put_card_screen(Card* card, bool result, int x, int y);

void show_hand_cards(Card** temp, bool* result, int count);

int select_card_screen();

void show_last_card(Card* lastcard);

void show_grab_card();

void attention_grab_card();

void draw_line_to_hold_thecards();

void show_player(int player_id, int x, int y);

void show_players(int aiplayercount);
#endif