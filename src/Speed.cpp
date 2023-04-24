#include "Speed.hpp"

Speed::Speed()
{
    number_ = 0;
}

Speed::~Speed()
{

}

void Speed::SetNumber(int &num_)
{
    number_ = num_;
}

void Speed::AddPos(const int &x_pos_)
{
    accelerate_pos_list_.push_back(x_pos_);
}

void Speed::Init(SDL_Renderer *des)
{
    bool load = Object::LoadImg("res/acceleration/speed.png", des);
    if (load)
    {
        number_ = 4;
        if (accelerate_pos_list_.size() > 0)
        {
            accelerate_pos_list_.clear();
        }

        AddPos(ACCELERATE_POS_1);
        AddPos(ACCELERATE_POS_2);
        AddPos(ACCELERATE_POS_3);
        AddPos(ACCELERATE_POS_4);
    }

    else
    {
        cout << "Fail to init heart" << endl;
    }
}

void Speed::Show(SDL_Renderer *des)
{
    for (int i = 0; i < accelerate_pos_list_.size(); i++)
    {
        rect_.x = accelerate_pos_list_.at(i);
        rect_.y = GROUND + 5;
        Object::RenderPos(rect_.x, rect_.y, des);
    }
}

void Speed::Move(SDL_Renderer *des)
{
    for (int i = 0; i < accelerate_pos_list_.size(); i++)
    {
        accelerate_pos_list_.at(i) -= 5;
        if (accelerate_pos_list_.at(i) + rect_.w < 0)
        {
            accelerate_pos_list_.erase(accelerate_pos_list_.begin());
        }
    }
}

void Speed::DecreaseAccelerate(float &acceleration, int &pos_)
{
    acceleration -= 0.5;
    number_--;
    accelerate_pos_list_.erase(accelerate_pos_list_.begin() + pos_);
}

vector<int> Speed::GetAccelerate()
{
    return accelerate_pos_list_;
}