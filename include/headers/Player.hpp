#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"
#include "Timer.hpp"

enum PLAYER_ACTION
{
    RUN,
    JUMP,
    FALL
};

class Player : public Object
{
    public:
        Player();
        ~Player();

        bool GetGround();
        void HandleInputAction(SDL_Event &events, Mix_Chunk *jump_wav_);
        void DoPlayer();
        bool LoadImg(string path, SDL_Renderer *screen);

        int GetFrameWidth();
        int GetFrameHeight();
        void UpdateImagePlayer(bool &is_lose_, SDL_Renderer *des);
        void Show(bool &is_lose_, SDL_Renderer *des);
        
        SDL_Rect GetPlayerObject();

    private:
        SDL_Rect player_object_;
        SDL_Rect frame_clip_[PLAYER_FRAMES];
        int frame_;
        double p_jump_;
        int width_frame_;
        int height_frame_;
        Timer player_timer_;
        int block_sprites_;
       
};

#endif