#include "Enemy.hpp"

Enemy::Enemy(int type)
{
    e_type_ = type;

    enemy_object_.w = 0;
    enemy_object_.h = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    id_frame_ = 0;

    block_sprites_ = 0;
}

Enemy::~Enemy()
{

}

bool Enemy::LoadImg(string path, SDL_Renderer *screen)
{
    bool load = false;
    if (e_type_ == AIR_ENEMY_TYPE)
    {
        for (int i = 0; i < AIR_ENEMY; i++)
        {
            if (path == IN_AIR[i])
            {
                e_air_ = i;
                break;
            }
        }
        load = Object::LoadImg(path.c_str(), screen);
        if (load == true)
        {
            width_frame_ = rect_.w / AIR_ENEMY_FRAMES[e_air_];
            height_frame_ = rect_.h;
            if (width_frame_ > 0 && height_frame_ > 0)
            {
                for (int i = 0; i < AIR_ENEMY_FRAMES[e_air_]; i++)
                {
                    frame_clip_[i].x = width_frame_ * i;
                    frame_clip_[i].y = 0;
                    frame_clip_[i].w = width_frame_;
                    frame_clip_[i].h = height_frame_;
                }
            }
        }
        else
        {
            cout << "Failed to load air enemy! " << endl;
        }
    }

    else if (e_type_ == GROUND_ENEMY_TYPE)
    {
        for (int i = 0; i < GROUND_ENEMY; i++)
        {
            if (path == ON_GROUND[i])
            {
                e_ground_ = i;
                break;
            }
        }

        load = Object::LoadImg(path.c_str(), screen);
        if (load == true)
        {
            width_frame_ = rect_.w / GROUND_ENEMY_FRAMES[e_ground_];
            height_frame_ = rect_.h;
            if (width_frame_ > 0 && height_frame_ > 0)
            {
                for (int i = 0; i < GROUND_ENEMY_FRAMES[e_ground_]; i++)
                {
                    frame_clip_[i].x = i * width_frame_;
                    frame_clip_[i].y = 0;
                    frame_clip_[i].w = width_frame_;
                    frame_clip_[i].h = height_frame_;
                }
            }

        }
        else
        {
            cout << "Failed to load ground enemy! " << endl;
        }
    }
    return load;
}

void Enemy::GenerateEnemy()
{
    if (e_type_ == AIR_ENEMY_TYPE)
    {
        enemy_object_.x = rand() % (ENEMY_POSITION_MAX_HELICOPTER - ENEMY_POSITION_MIN_HELICOPTER + 1) + (ENEMY_POSITION_MIN_HELICOPTER) + SCREEN_WIDTH;
        enemy_object_.y = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;  
        //cout << "Helicopter: " << enemy_object_.x << " " << enemy_object_.y << endl;
    }

    else if (e_type_ == GROUND_ENEMY_TYPE)
    {
        enemy_object_.y = GROUND;

        if (e_ground_ == CACTUS)
        {
            enemy_object_.x = rand() % (ENEMY_POSITION_MAX_CACTUS - ENEMY_POSITION_MIN_CACTUS + 1) + (ENEMY_POSITION_MIN_CACTUS) + SCREEN_WIDTH;
            //cout << "Cactus: " << enemy_object_.x << " " << endl;
        }

        else if (e_ground_ == MUMMY)
        {
            enemy_object_.x = rand() % (ENEMY_POSITION_MAX_MUMMY - ENEMY_POSITION_MIN_MUMMY + 1) + (ENEMY_POSITION_MIN_MUMMY) + SCREEN_WIDTH;
            //cout << "Mummy: " << enemy_object_.x << endl;
        }
    }
}

void Enemy::Move(const float &accelerate)
{
    if (e_type_ == AIR_ENEMY_TYPE)
    {
        if (e_air_ == HELICOPTER)
        {
            enemy_object_.x += - (ENEMY_SPEED + accelerate);
        }
        else if (e_air_ == VULTURE)
        {
            enemy_object_.x += - 2 * (ENEMY_SPEED + accelerate);
        }
    }

    else if (e_type_ == GROUND_ENEMY_TYPE)
    {
        if (e_ground_ == CACTUS)
        {
            enemy_object_.x += - (ENEMY_SPEED + accelerate);
        }
        else if (e_ground_ == MUMMY)
        {
            enemy_object_.x += - (ENEMY_SPEED + accelerate);
        }
    }
    
    if (enemy_object_.x + enemy_object_.w < 0)
    {
        GenerateEnemy();
    }
}

void Enemy::Show(SDL_Renderer *des)
{
    if (e_type_ == AIR_ENEMY_TYPE)
    {
        enemy_object_.w = frame_clip_[id_frame_].w;
        enemy_object_.h = frame_clip_[id_frame_].h;

        while (true)
        {
            if (block_sprites_ % 6 == 0)
            {
                id_frame_++;
            }

            if (id_frame_ == AIR_ENEMY_FRAMES[e_air_] - 1)
            {
                id_frame_ = 0;
                block_sprites_ = 0;
                break;
            }

            block_sprites_++;
            break;
        }
        SDL_RenderCopy(des, p_object_, &frame_clip_[id_frame_], &enemy_object_);
    }

    else if (e_type_ == GROUND_ENEMY_TYPE)
    {
        enemy_object_.w = frame_clip_[id_frame_].w;
        enemy_object_.h = frame_clip_[id_frame_].h;

        if (e_ground_ != CACTUS)
        {
            while (true)
            {
                if (block_sprites_ % 6 == 0)
                {
                    id_frame_++;
                }

                if (id_frame_ == GROUND_ENEMY_FRAMES[e_ground_] - 1)
                {
                    id_frame_ = 0;
                    block_sprites_ = 0;
                    break;
                }

                block_sprites_++;
                break;
            }
        }
        SDL_RenderCopy(des, p_object_, &frame_clip_[id_frame_], &enemy_object_);
    }
}

int Enemy::GetEnemyType()
{
    return e_type_;
}

int Enemy::GetAirEnemyType()
{
    return e_air_;
}

int Enemy::GetGroundEnemyType()
{
    return e_ground_;
}

SDL_Rect Enemy::GetEnemyObject()
{
    return enemy_object_;
}
