#include "Health.hpp"

Health::Health()
{
    number_ = 0;
}

Health::~Health()
{

}

void Health::SetNumber(int &num_)
{
    number_ = num_;
}

void Health::AddPos(const int &x_pos_)
{
    heart_pos_list_.push_back(x_pos_);
}

void Health::Init(SDL_Renderer *des)
{
    bool load = Object::LoadImg("res/heart/Heart.png", des);
    if (load)
    {
        number_ = 3;
        if (heart_pos_list_.size() > 0)
        {
            heart_pos_list_.clear();
        }

        AddPos(HEART_POS_1);
        AddPos(HEART_POS_2);
        AddPos(HEART_POS_3);

    }
    else
    {
        cout << "Fail to init heart" << endl;
    }
}
void Health::Show(SDL_Renderer *des)
{
    for (int i = 0; i < heart_pos_list_.size(); i++)
    {
        rect_.x = heart_pos_list_.at(i);
        rect_.y = 20;
        Object::RenderPos(rect_.x, rect_.y, des);
    }
}

void Health::IncreaseHeart()
{
    number_++;
    int last_pos_ = heart_pos_list_.back();
    last_pos_ += 40;
    heart_pos_list_.push_back(last_pos_); 
}

void Health::DecreaseHeart()
{
    number_--;
    heart_pos_list_.pop_back();
}

