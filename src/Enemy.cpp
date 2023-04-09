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
    enemy_timer_.Start();
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
    //int time_ = 0;

    if (e_type_ == AIR_ENEMY_TYPE)
    {
        enemy_object_.y = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 5) + ENEMY_MIN_HEIGHT;  //random tọa độ y
        if (e_air_ == HELICOPTER)                                                                 // loại enemy
        {


            enemy_object_.x = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;                       // random tọa độ x
            // if (enemy_object_.x - enemy_pos_[VULTURE] < ENEMY_POSITION_RANGE)                     // kiểm tra có trùng với enemy khác 

            // {                                                                                     // enemy_object_ có kiểu dữ liệu SDL_Rect
            //     enemy_object_.x = ENEMY_POSITION_RANGE + enemy_pos_[VULTURE];                     // biến enemy_pos_ có kiểu dữ liệu map
            // }
            // enemy_pos_[e_air_] = enemy_object_.x;
            

        }

        else if (e_air_ == VULTURE)
        {
            // while (time_ <= 50)
            // {
            //     time_++;
            //     if (time_ == 50)
            //     {
                    enemy_object_.x = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
                    // if (enemy_object_.x - enemy_pos_[HELICOPTER] < ENEMY_POSITION_RANGE)
                    // {
                    //     enemy_object_.x = ENEMY_POSITION_RANGE + enemy_pos_[HELICOPTER];
                    // }
                    // enemy_pos_[e_air_] = enemy_object_.x;
            //         time_ = 0;
            //         break;
            //     }
            // }

        }
    }
    else if (e_type_ == GROUND_ENEMY_TYPE)
    {
        enemy_object_.y = GROUND;

        if (e_ground_ == CACTUS)
        {
            // while (time_ <= 25)
            // {
            //     time_++;
            //     if (time_ == 25)
            //     {
                    enemy_object_.x = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
            //         if (enemy_object_.x - enemy_pos_[DOUBLE_CACTUS] < ENEMY_POSITION_RANGE)
            //         {
            //             enemy_object_.x = ENEMY_POSITION_RANGE + enemy_pos_[DOUBLE_CACTUS];
            //         }
            //         enemy_pos_[e_ground_] = enemy_object_.x;
            // //         time_ = 0;
            //         break;
            //     }
            // }
        }

        else if (e_ground_ == DOUBLE_CACTUS)
        {
            // while (time_ <= 50)
            // {
            //     time_++;
            //     if (time_ == 50)
            //     {
                    enemy_object_.x = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
                    // if (enemy_object_.x - enemy_pos_[MUMMY] < ENEMY_POSITION_RANGE)
                    // {
                    //     enemy_object_.x = ENEMY_POSITION_RANGE + enemy_pos_[MUMMY];
                    // }
                    // enemy_pos_[e_ground_] = enemy_object_.x;
            //         time_ = 0;
            //         break;
            //     }
            // }
        }

        else if (e_ground_ == MUMMY)
        {
            // while (time_ <= 75)
            // {
            //     time_++;
            //     if (time_ == 75)
            //     {
                    enemy_object_.x = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
                    // if (enemy_object_.x - enemy_pos_[SCORPIO] < ENEMY_POSITION_RANGE)
                    // {
                    //     enemy_object_.x = ENEMY_POSITION_RANGE + enemy_pos_[SCORPIO];
                    // }
                    // enemy_pos_[e_ground_] = enemy_object_.x;
            //         time_ = 0;
            //         break;
            //     }
            // }
        }

        else if (e_ground_ == SCORPIO)
        {
            // while (time_ <= 100)
            // {
            //     time_++;
            //     if (time_ == 100)
            //     {
                    enemy_object_.x = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
                    // if (enemy_object_.x - enemy_pos_[CACTUS] < ENEMY_POSITION_RANGE)
                    // {
                    //     enemy_object_.x = ENEMY_POSITION_RANGE + enemy_pos_[CACTUS];
                    // }
                    // enemy_pos_[e_ground_] = enemy_object_.x;
            //         time_ = 0;
            //         break;
            //     }
            // }
        }
    }

//   SDL_Delay(5);
}

void Enemy::Move(const int &accelerate)
{
    enemy_object_.x += -(ENEMY_SPEED + accelerate);
    if (enemy_object_.x + enemy_object_.w <= 0)
    {
        enemy_object_.x = rand() % (ENEMY_POSITION_RANGE) + SCREEN_WIDTH;

        if (e_type_ == AIR_ENEMY_TYPE)
        {
            enemy_object_.y = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 5) + ENEMY_MIN_HEIGHT;
        }
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
            if (block_sprites_ % 5 == 0)
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

        if (e_ground_ != CACTUS && e_ground_ != DOUBLE_CACTUS)
        {
            while (true)
            {
                if (block_sprites_ % 5 == 0)
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
