#include "Button.hpp"

Button::Button()
{
    b_width_ = 0;
    b_height_ = 0;
    mouse_state_ = NORMAL;
}

Button::~Button()
{

}

bool Button::LoadImg(string path, SDL_Renderer *screen)
{
    bool load = Object::LoadImg(path.c_str(), screen);
    if (load == true)
    {
        b_width_ = rect_.w / BUTTON_FRAMES;
        b_height_ = rect_.h;
        if (b_width_ > 0 && b_height_ > 0)
        {
            for (int i = 0; i < BUTTON_FRAMES; i++)
            {
                frame_clip_[i].x = b_width_ * i;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = b_width_;
                frame_clip_[i].h = b_height_;
            }
        }
    }
    else
    {
        cout << "Failed to load button image" << endl;
    }
    return load;
}

void Button::SetPosition(int x, int y)
{
    button_object_.x = x;
    button_object_.y = y;
}

void Button::SetMouseState(const int &state_)
{
    mouse_state_ = state_;
}

bool Button::IsInside(SDL_Event &event)
{
    bool inside = false;
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        inside = (x >= button_object_.x) && (x <= button_object_.x + b_width_) && (y >= button_object_.y) && (y <= button_object_.y + b_height_);
    }
    return inside;  
}

void Button::RenderButton(SDL_Renderer *des)
{
    button_object_.w = frame_clip_[mouse_state_].w;
    button_object_.h = frame_clip_[mouse_state_].h;

    SDL_RenderCopy(des, p_object_, &frame_clip_[mouse_state_], &button_object_);
}

SDL_Rect Button::GetButtonRect()
{
    return button_object_;
}