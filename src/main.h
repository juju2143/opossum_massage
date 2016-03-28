/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#include "WRAPPER/API.h"
#include "WRAPPER/INPUT.h"

#define TITLESCREEN 0
#define STORY 1
#define GAME 2
#define GAMEOVER 3

char string_score[12];
char highscore_string[12];
unsigned int highscore = 0;
unsigned int score = 0;

unsigned char image_story = 0;
unsigned char story_transition = 0;
short story_x = 0;
unsigned char start_game = 0;
unsigned short gameover_time = 0;
unsigned char carre_tension = 52;

unsigned char game_mode;
unsigned char start_pressed;
unsigned char start_time;

void title_logic();
void story_logic();
void fleche_logic(void);
void game_logic();
void gameover_logic();

void Load_Font();
void Print_text(int x, int y, char *text_ex);

short rand_a_b(short a, short b);
void reset_settings();

#define uint32_t unsigned int

uint32_t ReadLongLittleEndian (FILE* output) ;
void WriteIntLittleEndian (uint32_t long_in, FILE* output);
void Load_score();
void Save_score();

void Print_text(int x, int y, char *text_ex)
{
	int i = 0;

	for (i=0;text_ex[i]!='\0';i++)
	{
		Put_sprite(100/*+i*/, x + (6 * i), y, 6, 11, text_ex[i]-33);
	}
}

void Load_Font()
{
	/*int i;*/
	Load_Image(100,"data/font.bmp");
	/*for(i=101;i<108;i++)
	{
		Copy_Image(100,i);
	}*/
}
