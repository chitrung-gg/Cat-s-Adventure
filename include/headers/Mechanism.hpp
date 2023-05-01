#ifndef MECHANISM_HPP_
#define MECHANISM_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Timer.hpp"
#include "Button.hpp"
#include "Speed.hpp"

#define TIME_MAX 3000
#define SPEED_ACCELERATE 1
#define TIME_ACCELERATE 1
#define SCORE_ACCELERATE 1
#define SCORE_POS_X 630
#define SCORE_POS_Y 20
#define HIGHSCORE_POS_X 720
#define HIGHSCORE_POS_Y 60

class Mechanism
{
    public:
        void RenderScrollingBackground(vector<float> &speed_layer_, float &acceleration, Object (&Background)[BACKGROUND_LAYER], SDL_Renderer *screen);
        void RenderScrollingGround(int &speed, const int acceleration, Object &Ground, SDL_Renderer *screen);

        bool CheckCollision(Player &player, Enemy &enemy);
        bool CheckAccelerationCollision(Player &player_, Speed &acceleration_, int pos_);
        void ControlFPS(Timer &timer);

        string GetHighScore (string path);
        void UpdateHighScore(const int &score, string path);
        void DrawScore(Object &o_score_, Timer &o_timer_, SDL_Renderer *des, TTF_Font *font, SDL_Color color, int &time, float &acceleration, int &score);
        void DrawHighScore(Object &o_highscore_, /*Timer &o_timer_ */ SDL_Renderer *des, TTF_Font *font, SDL_Color color);
        void ChangeGameState(bool &play_, bool &is_running_, bool &is_lose_);
    private:

};

#endif