#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"

const int HEART_POS_1 = 440;
const int HEART_POS_2 = 480;
const int HEART_POS_3 = 520;

class Health: public Object
{
    public:
        Health();
        ~Health();

        void SetNumber(int &num_);
        void AddPos(const int &x_pos_);
        void Init(SDL_Renderer *des);
        void Show(SDL_Renderer *des);
        
        void IncreaseHeart();
        void DecreaseHeart();

    private:
        int number_;
        vector<int> heart_pos_list_;
    
};

#endif