#include "Mechanism.hpp"

void Mechanism::RenderScrollingBackground(vector<float> &speed_layer_, const int acceleration, Object (&Background)[BACKGROUND_LAYER], SDL_Renderer *screen)
{
    vector<float> layer_speed;
    layer_speed.push_back(LAYER_0_SPEED);
    layer_speed.push_back(LAYER_1_SPEED);
    layer_speed.push_back(LAYER_2_SPEED);
    layer_speed.push_back(LAYER_3_SPEED);

    vector<float> layer_acceleration;
    layer_acceleration.push_back(acceleration / 10);
    layer_acceleration.push_back(acceleration / 8);
    layer_acceleration.push_back(acceleration / 6);
    layer_acceleration.push_back(acceleration / 4);
    
    for (int i = 0; i < BACKGROUND_LAYER; i++)
    {
        speed_layer_[i] -= layer_speed[i] + layer_acceleration[i];
        if (speed_layer_[i] + Background[i].GetWidth() < 0)
        {
            speed_layer_[i] = 0;
        }
        Background[i].RenderPos(speed_layer_[i], 0, screen);
        Background[i].RenderPos(speed_layer_[i] + Background[i].GetWidth(), 0, screen);
    }
}

void Mechanism::RenderScrollingGround(int &speed, const int acceleration, Object &Ground, SDL_Renderer *screen)
{
    speed -= LAYER_GROUND_SPEED + acceleration;
    if (speed + Ground.GetWidth() < 0)
    {
        speed = 0;
    }
    Ground.RenderPos(speed, 0, screen);
    Ground.RenderPos(speed + Ground.GetWidth(), 0, screen);
}

bool Mechanism::CheckCollision(Player &player, Enemy &enemy)
{
    SDL_Rect obj_1 = player.GetPlayerObject();
    SDL_Rect obj_2 = enemy.GetEnemyObject();

    int p_left, e_left;
    int p_right, e_right;
    int p_top, e_top;
    int p_bottom, e_bottom;

    p_left = obj_1.x;
    p_right = obj_1.x + obj_1.w;
    p_top = obj_1.y;
    p_bottom = obj_1.y + obj_1.h;

    e_left = obj_2.x;
    e_right = obj_2.x + obj_2.w;
    e_top = obj_2.y;
    e_bottom = obj_2.y + obj_2.h;

    if (((p_bottom <= e_top) || (p_top >= e_bottom) || (p_right <= e_left) || (p_left >= e_right)) == false)
    {
        return true;
    }
    return false;
}

void Mechanism::ControlFPS(Timer &timer)
{
    int real_time_ = timer.GetTicks();
    int time_per_frame_ = 1000 / FPS;

    if (real_time_ < time_per_frame_)
    {
        SDL_Delay(time_per_frame_ - real_time_);
    }
}

string Mechanism::GetHighScore(string path)
{
    string high_score_;
    ifstream score_file_(path.c_str());
    if (score_file_.is_open())
    {
        getline(score_file_, high_score_);
    }
    else high_score_ = "Unable to open file! ";
    score_file_.close();
    return high_score_;
}

void Mechanism::UpdateHighScore(const int &score, string path)
{
    if (score > stoi(GetHighScore(path.c_str())))
    {
        ofstream score_file (path.c_str());
        score_file << to_string(score);
        score_file.close();
    }
}

void Mechanism::DrawScore(Object &o_score_, Timer &o_timer_, SDL_Renderer *des, TTF_Font *font, SDL_Color color, int &time, int &acceleration, int &score)
{
    if (time >= TIME_MAX) 
    {
        acceleration += SPEED_ACCELERATE;
        time = 0;
    }

    if (time % 25 == 0 && !o_timer_.IsPaused())
    {
        score += SCORE_ACCELERATE;
    }

    time += TIME_ACCELERATE;
    string new_score_ = "CURRENT SCORE: " + to_string(score);

    o_score_.LoadRenderedText(new_score_.c_str(), font, color, des);     
    o_score_.RenderPos(SCORE_POS_X, SCORE_POS_Y, des);
    o_score_.Free();   
}

void Mechanism::DrawHighScore(Object &o_highscore_, SDL_Renderer *des, TTF_Font *font, SDL_Color color)
{
    string high_score_ = "HIGH SCORE: " + GetHighScore("res/highscore.txt");

    o_highscore_.LoadRenderedText(high_score_, font, color, des);
    o_highscore_.RenderPos(HIGHSCORE_POS_X, HIGHSCORE_POS_Y, des);
    o_highscore_.Free();
}

void Mechanism::DrawLoseGame(bool &play_, bool &is_running_, bool &is_lose_, SDL_Renderer *des)
{
    is_lose_ = true;
    play_ = false;
    SDL_Texture *new_Texture = nullptr;
    SDL_Surface *load_surface = IMG_Load("res/menu/notification.png");
    if (load_surface != nullptr)
    {
        // Xóa những cái background đằng sau ảnh của character (transparent)
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR));
        new_Texture = SDL_CreateTextureFromSurface(des, load_surface);
        if (new_Texture == nullptr)
        {
            cout << "Failed to create texture" << endl;
            // Surface dang luu thong so anh
        }

        SDL_FreeSurface(load_surface);
    }
    else 
    {
        cout << "Failed to load lose image!" << endl;
    }

    SDL_RenderCopy(des, new_Texture, nullptr, nullptr);
    SDL_DestroyTexture(new_Texture);
}