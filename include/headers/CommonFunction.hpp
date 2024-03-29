#ifndef COMMON_FUNCTION_HPP_
#define COMMON_FUNCTION_HPP_

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

//Screen

const int REPEAT_SOUND = -1;
const int NOT_REPEAT_SOUND = 0;
const int CHUNK_CHANNEL = -1;
const string WINDOW_TITLE = "Cat's Adventure";
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 576;

const int COLOR_KEY_R = 0xff;
const int COLOR_KEY_G = 0xff;
const int COLOR_KEY_B = 0xff;

const int RENDER_DRAW_COLOR = 0xff;

const int BACKGROUND_LAYER = 4;
const int BACKGROUND_TYPE = 4;
const int GROUND_LAYER = 1;
const string LAYER [BACKGROUND_TYPE][BACKGROUND_LAYER] 
{
    {"res/background/1/0.png", "res/background/1/1.png", "res/background/1/2.png", "res/background/1/3.png"},
    {"res/background/2/0.png", "res/background/2/1.png", "res/background/2/2.png", "res/background/2/3.png"},
    {"res/background/3/0.png", "res/background/3/1.png", "res/background/3/2.png", "res/background/3/3.png"},
    {"res/background/4/0.png", "res/background/4/1.png", "res/background/4/2.png", "res/background/4/3.png"}
};

const string LAYER_GROUND[BACKGROUND_TYPE]
{
    "res/background/1/4.png", 
    "res/background/2/4.png",
    "res/background/3/4.png",
    "res/background/4/4.png"
};

const int PLAYER_RUNNING_LAYER = 8;
const int PLAYER_FRAMES = 8;

const float LAYER_0_SPEED = 0.5;
const float LAYER_1_SPEED = 0.75;
const float LAYER_2_SPEED = 1;
const float LAYER_3_SPEED = 1.25;
const float LAYER_GROUND_SPEED = 2;

const int FPS = 60;

#define PLAYER_POS_X 100
#define GROUND 452
#define MAX_JUMP 15
#define FALL_SPEED 0.675
#define INIT_SPEED 0


#endif