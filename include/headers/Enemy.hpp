#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"
#include "Timer.hpp"

const int ENEMY_SPEED = 3;
const int MAX_ENEMY_FRAMES = 5;
const int AIR_ENEMY_TYPE = 1;
const int GROUND_ENEMY_TYPE = 2;

const int AIR_ENEMY = 2;
const int GROUND_ENEMY = 2;

const int AIR_ENEMY_FRAMES[AIR_ENEMY] = {4, 4};
const int GROUND_ENEMY_FRAMES[GROUND_ENEMY] = {1, 6};

static const string IN_AIR[AIR_ENEMY]
{
    "res/enemy/Helicopter.png",
    "res/enemy/Vulture.png"
};

static const string ON_GROUND[GROUND_ENEMY]
{
    "res/enemy/Cactus.png",
    "res/enemy/Mummy.png"
};

const int ENEMY_RANGE = 225;
const int ENEMY_MIN_HEIGHT = 270;
const int ENEMY_MAX_HEIGHT = 330;

const int ENEMY_POSITION_MIN_HELICOPTER = 323;
const int ENEMY_POSITION_MAX_HELICOPTER = 337;

const int ENEMY_POSITION_MIN_VULTURE = 123;
const int ENEMY_POSITION_MAX_VULTURE = 137;

const int ENEMY_POSITION_MIN_CACTUS = 23;
const int ENEMY_POSITION_MAX_CACTUS = 37;

const int ENEMY_POSITION_MIN_MUMMY = 123;
const int ENEMY_POSITION_MAX_MUMMY = 137;

const int GROUND_HEIGHT = 18;

enum ENEMY_AIR
{
    HELICOPTER,
    VULTURE
};

enum ENEMY_GROUND
{
    CACTUS,
    MUMMY
};

class Enemy : public Object
{
    public:
        Enemy(int type);
        ~Enemy();

        bool LoadImg(string path, SDL_Renderer *screen);
        void GenerateEnemy();
        void AddEnemy(int &x_pos_);
        void Move(const int &acceleration);
        void Show(SDL_Renderer *des);
        void Ignore();
        //bool CheckEnemyCollision(Enemy &enemy_1_, Enemy &enemy_2_);

        int GetEnemyType();
        int GetAirEnemyType();
        int GetGroundEnemyType();

        SDL_Rect GetEnemyObject();
    private:
        int e_air_, e_ground_;
        int e_type_;
        int id_frame_;
        SDL_Rect enemy_object_;
        int width_frame_;
        int height_frame_;
        SDL_Rect frame_clip_[MAX_ENEMY_FRAMES];
        Timer enemy_timer_;
        int block_sprites_;
        vector<int> enemy_spawn_;
};

#endif