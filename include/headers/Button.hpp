#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"

enum BUTTON_STATUS
{
    NORMAL,
    HOVER,
    CLICK,
};

#define PLAY_BUTTON_POS_X 330
#define PLAYBUTTON_POS_Y 320

#define HIGHSCORES_BUTTON_POS_X 430
#define HIGHSCORES_BUTTON_POS_Y 320

#define INFORMATION_BUTTON_POS_X 530
#define INFORMATION_BUTTON_POS_Y 320

#define MUSIC_ENABLE_BUTTON_POS_X 0
#define MUSIC_ENABLE_BUTTON_POS_Y 64

#define MUSIC_DISABLE_BUTTON_POS_X 0
#define MUSIC_DISABLE_BUTTON_POS_Y 64

#define EXIT_BUTTON_POS_X 630
#define EXIT_BUTTON_POS_Y 320

#define RETURN_BUTTON_POS_X 320
#define RETURN_BUTTON_POS_Y 240

#define PAUSE_BUTTON_POS_X 0
#define PAUSE_BUTTON_POS_Y 0

#define BUTTON_FRAMES 3

class Button : public Object
{
    public:
        Button();
        ~Button();

        bool LoadImg(string path, SDL_Renderer *screen);

        void SetPosition(int x, int y);
        void SetMouseState(const int &state_);
        bool IsInside(SDL_Event &event);
        //void HandleAction(SDL_Event &event);
        void RenderButton(SDL_Renderer *des);

        SDL_Rect GetButtonRect();

    private:
        SDL_Rect frame_clip_[BUTTON_FRAMES];
        SDL_Rect button_object_;
        int b_width_;
        int b_height_;
        int mouse_state_;
};
#endif