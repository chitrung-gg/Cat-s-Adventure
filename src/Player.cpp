#include "Player.hpp"

Player::Player()
{
    player_object_.x = PLAYER_POS_X;
    player_object_.y = GROUND;
    p_jump_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    block_sprites_ = 0;
}

Player::~Player()
{
    Free();
}

bool Player::GetGround()
{
    return player_object_.y == GROUND;
}

void Player::HandleInputAction(SDL_Event &events, Mix_Chunk *jump_wav_)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP : case SDLK_SPACE :
            Mix_PlayChannel(CHUNK_CHANNEL, jump_wav_, NOT_REPEAT_SOUND);
            if (GetGround() == true)
            {   
                p_jump_ = MAX_JUMP;       
            }
            break;
        default:
            break;
        }
    }
}

void Player::DoPlayer()
{
    p_jump_ -= FALL_SPEED;
    player_object_.y += -p_jump_;
    if (player_object_.y >= GROUND) 
    {
        p_jump_ = FALL_SPEED;
    }
    player_object_.y = min(player_object_.y, GROUND);
}



bool Player::LoadImg(string path, SDL_Renderer *screen)
{
    bool load = Object::LoadImg(path.c_str(), screen);
    if (load == true)
    {
        width_frame_ = rect_.w / PLAYER_FRAMES;
        height_frame_ = rect_.h;
        if (width_frame_ > 0 && height_frame_ > 0)
        {
            for (int i = 0; i < PLAYER_FRAMES; i++)
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
        cout << "Failed to load player image" << endl;
    }
    return load;
}

int Player::GetFrameWidth()
{
    return width_frame_;
}

int Player::GetFrameHeight()
{
    return height_frame_;
}

void Player::UpdateImagePlayer(SDL_Renderer *des)
{
    if (!GetGround())
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = nullptr;
        LoadImg("res/cat/Fall.png", des);
    }
    else
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = nullptr;
        LoadImg("res/cat/Run.png", des);
    }
}

void Player::Show(SDL_Renderer *des)
{
    UpdateImagePlayer(des);

    player_object_.w = frame_clip_[frame_].w;
    player_object_.h = frame_clip_[frame_].h;

    while (true)
    {
        if (block_sprites_ % 5 == 0)
        {
            frame_++;
        }

        if (frame_ == PLAYER_FRAMES - 1)
        {
            frame_ = 0;
            block_sprites_ = 0;
            break;
        }

        block_sprites_++;
        break;
    }
    SDL_RenderCopy(des, p_object_, &frame_clip_[frame_], &player_object_);
    
}

SDL_Rect Player::GetPlayerObject()
{
    return player_object_;
}