/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "main_nspire.h"

unsigned char done = 0;

int main ( int argc, char* argv[] )
{
	enable_relative_paths(argv);
	
	highscore = 0;
	score = 0;
    reset_settings();
    
    Load_score();
    
    initBuffering();
    clearBufferB();
    updateScreen();
	
    while (!done)
    {
		if (isKeyPressed(KEY_NSPIRE_ESC)) done = 1;
        
        switch(game_mode)
        {
			case TITLESCREEN:
				title_logic();
			break;
			case STORY:
				clearBufferB();
				story_logic();
			break;
			case GAME:
				game_logic();
			break;
			case GAMEOVER:
				clearBufferB();
				gameover_logic();
			break;
		}

        updateScreen();

    } 
    
    deinitBuffering();
    return 0;
}

void game_logic()
{
	
	static unsigned char animation_oldman = 0;
	static unsigned char time_oldman = 0;
	unsigned char animation_oldman_frames[3] = {0, 1, 126};
	static unsigned char carre_time = 0;
	static unsigned char carre_reserve = 0;
	static unsigned char carre_time_reserve = 0;
	static unsigned char start_time = 0;
	unsigned char temp_random;
	unsigned char lim;
	Rect oldman_spr;
	oldman_spr.w = 96;
	oldman_spr.h = 100;
	oldman_spr.x = oldman_spr.w * (animation_oldman_frames[animation_oldman]);
	oldman_spr.y = 0;
	
	drawSprite(img_game, 0, 0, 0, 0);
	drawSprite(img_score, 100, 7, 0, 0);
	drawSprite(img_white, 104+carre_tension, 22, 0,0);
	
    sprintf(string_score, "%d", score);
    Print_text(160, 7, string_score);
	
	drawSpritePart(img_oldman, 104, 108, &oldman_spr, 0, 0);
	
	switch (start_game)
	{
		case 0:
			drawSprite(img_ready, 136, 112, 0,0);
			start_time++;
			if (start_time > 60)
			{
				start_game = 1;
				start_time = 0;
			}
		break;	
		case 1:
			score++;
			carre_time++;
			carre_time_reserve++;
			time_oldman++;
			
			if (carre_tension < 1 || carre_tension > 103)
			{
				game_mode = GAMEOVER;
			}
			
			if (score > 2000)
			{
				lim = 4;
			}
			else if (score > 1250)
			{
				lim = 3;
			}
			else if (score > 500)
			{
				lim = 1;
			}
			else
			{
				lim = 0;
			}
			

			if (carre_time_reserve > 0)
			{
				while (carre_reserve > 0) 
				{
					temp_random = rand_a_b(1, 3);
					carre_reserve = carre_reserve - 1;
					carre_tension = (carre_tension + temp_random + lim);
				}
				carre_time_reserve = 0;
			}
			
			if (carre_time > 0)
			{
				temp_random = 2;
				carre_tension = carre_tension - (temp_random + lim);
				carre_time = 0;
			}
			
			if (isKeyPressed(KEY_NSPIRE_CTRL))
			{
				if (time_oldman > 2)
				{
					animation_oldman++;
					if (animation_oldman_frames[animation_oldman] == 126) animation_oldman = 0;
					time_oldman = 0;
				}
				carre_reserve = carre_reserve + 3;
			}
		break;		
	}

}

void title_logic()
{
	static unsigned char red_time = 0;
	drawSprite(img_title, 0, 0, 0,0);
	
	if (isKeyPressed(KEY_NSPIRE_CTRL) && start_pressed == 0)
	{
		start_pressed = 1;
		red_time = 0;
		start_time = 0;
	}
	
	if (start_pressed == 1)
	{
		start_time++;
		red_time++;
		
		if (start_time < 20)
		{
			if (red_time < 4)
			{
				drawSprite(img_red, 0, 0, 0,0);
			}
			else if (red_time > 8)
			{
				drawSprite(img_title, 0, 0, 0,0);
			}
			else
			{
				red_time = 0;
			}
		}
		else if (start_time > 80)
		{
			game_mode = STORY;
		}
	}
	else
	{
		drawSprite(img_hi, 240, 208, 0,0);
		Print_text(240, 224, highscore_string);	
	}
}


void story_logic()
{
	switch(image_story)
	{
		case 0:
			drawSprite(img_story1, story_x, 0, 0,0);
		break; 
		case 1:
			drawSprite(img_story2, story_x, 0, 0,0);
		break; 
		case 2:
			drawSprite(img_story3, story_x, 0, 0,0);
		break; 
	}
	
	if (isKeyPressed(KEY_NSPIRE_CTRL) && story_transition == 0)
	{
		story_transition = 1;
	}
	
	if (story_transition > 0)
	{
		story_x = story_x + 16;
		if (story_x > 320)
		{
			image_story++;
			story_transition = 2;
			story_x = -320;
		}
		
		if (story_transition == 2 && story_x == 0)
		{
			story_transition = 0;
			if (image_story == 3) game_mode = GAME;
		}
	}
	else
	{
		fleche_logic();
	}
}

void fleche_logic(void)
{
	static unsigned char fleche_frame = 0;
	static unsigned char fleche_time = 0;
	unsigned char fleche_animation[10] = {0, 1, 2, 3, 2, 1, 126};
	Rect fleche_rect;
	fleche_rect.w = 16;
	fleche_rect.h = 16;
	fleche_rect.x = 16 * fleche_animation[fleche_frame];
	fleche_rect.y = 0;
	
	fleche_time++;
	
	if (fleche_time > 2)
	{
		fleche_frame++;
		fleche_time = 0;
	}
	
	if (fleche_animation[fleche_frame] == 126)
	{
		fleche_frame = 0;
	}
	
	drawSpritePart(img_fleche, 304, 224, &fleche_rect, 0, 0);
}

void gameover_logic()
{
	short possum_x_positions[5] = {-20, 0, 20, 126};
	static unsigned char animation_possum = 0;
	
	animation_possum++;
	gameover_time++;
	if (animation_possum > 4) animation_possum = 0;
	
	drawSprite(img_possum, possum_x_positions[animation_possum], 0, 0, 0);
	drawSprite(img_gameover, 80, 16, 0, 0);
	
	if (gameover_time > 120)
	{
		reset_settings();
	}
}


void reset_settings()
{
	if (highscore < score) 
	{	
		highscore = score;
		sprintf(highscore_string, "%d", highscore);
		Save_score();
	}
	
	game_mode = TITLESCREEN;
	start_pressed = 0;
	start_time = 0;
	image_story = 0;
	story_transition = 0;
	story_x = 0;
	start_game = 0;
	gameover_time = 0;
	score = 0;
	carre_tension = 52;
}

// Used for random coordinate for the clouds
short rand_a_b(short a, short b)
{
    return rand()%(b-a) +a;
}

void Load_score()
{
	FILE* file;
	file = fopen("./possum.save.tns", "r+");
		
	if (file)
	{
		highscore = ReadLongLittleEndian (file);
	}
	else
	{
		// If the file does not exist then create it
		file = fopen("./possum.save", "w");
		highscore = 0;
	}
	
	sprintf(highscore_string, "%d", highscore);
		
	fclose(file);
}

void Save_score()
{
	FILE* file;

	file = fopen("./possum.save.tns", "w+");
	
	WriteIntLittleEndian(highscore, file);
		
	fclose(file);
}


/*
 * Theses routines were done by Lionel Debroux 
 * Many thanks to him ! (Now, i don't have to use modulo & divisions)
*/

uint32_t ReadLongLittleEndian (FILE* output) 
{
    uint32_t temp_long;
    temp_long  = fgetc(output);
    temp_long |= fgetc(output) << 8;
    temp_long |= fgetc(output) << 16;
    temp_long |= fgetc(output) << 24;
    return temp_long;
}

void WriteIntLittleEndian (uint32_t long_in, FILE* output)  
{
    fputc (((int)(long_in      )) & 0xFF, output);
    fputc (((int)(long_in >>  8)) & 0xFF, output);
    fputc (((int)(long_in >> 16)) & 0xFF, output);
    fputc (((int)(long_in >> 24)) & 0xFF, output);
    fflush(output);
}

