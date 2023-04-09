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
const int GROUND_LAYER = 1;
const string LAYER [BACKGROUND_LAYER] 
{
    "res/background/4/0.png",
    "res/background/4/1.png",
    "res/background/4/2.png",
    "res/background/4/3.png"
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
#define GROUND 445
#define MAX_JUMP 10
#define FALL_SPEED 0.5
#define INIT_SPEED 0


#endif
