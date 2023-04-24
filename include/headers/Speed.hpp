#ifndef SPEED_HPP_
#define SPEED_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"

const int ACCELERATE_POS_1 = 2200;
const int ACCELERATE_POS_2 = 3000;
const int ACCELERATE_POS_3 = 3750;
const int ACCELERATE_POS_4 = 5000;

class Speed: public Object
{
    public:
        Speed();
        ~Speed();

        void SetNumber(int &num_);
        void AddPos(const int &x_pos_);
        void Init(SDL_Renderer *des);
        void Show(SDL_Renderer *des);
        void Move(SDL_Renderer *des);
        
        void DecreaseAccelerate(float &acceleration, int &pos_);
        vector<int> GetAccelerate();

    private:
        int number_;
        vector<int> accelerate_pos_list_;
    
};

#endif