#include "Mechanism.hpp"

void Mechanism::RenderScrollingBackground(vector<float> &speed_layer_, float &acceleration, Object (&Background)[BACKGROUND_LAYER], SDL_Renderer *screen)
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
    SDL_Rect p_rect_ = player.GetPlayerObject();
    SDL_Rect e_rect_ = enemy.GetEnemyObject();

    int p_left, e_left;
    int p_right, e_right;
    int p_top, e_top;
    int p_bottom, e_bottom;

    int PLAYER_TRASH_PIXEL_X, PLAYER_TRASH_PIXEL_Y;
    int PLAYER_TRASH_PIXEL_W, PLAYER_TRASH_PIXEL_H;
    int ENEMY_TRASH_PIXEL_X, ENEMY_TRASH_PIXEL_Y;
    int ENEMY_TRASH_PIXEL_W, ENEMY_TRASH_PIXEL_H;

    PLAYER_TRASH_PIXEL_X = 20;
    PLAYER_TRASH_PIXEL_Y = 6;
    PLAYER_TRASH_PIXEL_W = 28;
    PLAYER_TRASH_PIXEL_H = 5;

    if (enemy.GetEnemyType() == AIR_ENEMY_TYPE)
    {
        if (enemy.GetAirEnemyType() == HELICOPTER)
        {
            ENEMY_TRASH_PIXEL_X = 12;
            ENEMY_TRASH_PIXEL_Y = 5;
            ENEMY_TRASH_PIXEL_W = 12;
            ENEMY_TRASH_PIXEL_H = 4;
        }
        if (enemy.GetAirEnemyType() == VULTURE)
        {
            ENEMY_TRASH_PIXEL_X = 12;
            ENEMY_TRASH_PIXEL_Y = 29;
            ENEMY_TRASH_PIXEL_W = 8;
            ENEMY_TRASH_PIXEL_H = 6;

        }
    }

    else if (enemy.GetEnemyType() == GROUND_ENEMY_TYPE)
    {
        if (enemy.GetGroundEnemyType() == CACTUS)
        {
            ENEMY_TRASH_PIXEL_X = 12;
            ENEMY_TRASH_PIXEL_Y = 2;
            ENEMY_TRASH_PIXEL_W = 9;
            ENEMY_TRASH_PIXEL_H = 2;
        }
        if (enemy.GetGroundEnemyType() == MUMMY)
        {
            ENEMY_TRASH_PIXEL_X = 21;
            ENEMY_TRASH_PIXEL_Y = 22;
            ENEMY_TRASH_PIXEL_W = 7;
            ENEMY_TRASH_PIXEL_H = 1;
        }
    }

    p_left = p_rect_.x + PLAYER_TRASH_PIXEL_X;
    p_right = p_rect_.x + p_rect_.w - PLAYER_TRASH_PIXEL_W;
    p_top = p_rect_.y + PLAYER_TRASH_PIXEL_Y;
    p_bottom = p_rect_.y + p_rect_.h - PLAYER_TRASH_PIXEL_H;

    e_left = e_rect_.x + ENEMY_TRASH_PIXEL_X;
    e_right = e_rect_.x + e_rect_.w - ENEMY_TRASH_PIXEL_W;
    e_top = e_rect_.y + ENEMY_TRASH_PIXEL_Y;
    e_bottom = e_rect_.y + e_rect_.h - ENEMY_TRASH_PIXEL_H;

    if (((p_bottom <= e_top) || (p_top >= e_bottom) || (p_right <= e_left) || (p_left >= e_right)) == false)
    {
        return true;
    }
    return false;
}

bool Mechanism::CheckAccelerationCollision(Player &player_, Speed &acceleration_, int pos_)
{
    SDL_Rect p_rect_ = player_.GetPlayerObject();
    SDL_Rect a_rect_ = acceleration_.GetRect();

    int p_left, a_left;
    int p_right, a_right;
    int p_top, a_top;
    int p_bottom, a_bottom;

    int PLAYER_TRASH_PIXEL_X, PLAYER_TRASH_PIXEL_Y;
    int PLAYER_TRASH_PIXEL_W, PLAYER_TRASH_PIXEL_H;
    int ENEMY_TRASH_PIXEL_X, ENEMY_TRASH_PIXEL_Y;
    int ENEMY_TRASH_PIXEL_W, ENEMY_TRASH_PIXEL_H;

    PLAYER_TRASH_PIXEL_X = 20;
    PLAYER_TRASH_PIXEL_Y = 6;
    PLAYER_TRASH_PIXEL_W = 28;
    PLAYER_TRASH_PIXEL_H = 5;

    p_left = p_rect_.x + PLAYER_TRASH_PIXEL_X;
    p_right = p_rect_.x + p_rect_.w - PLAYER_TRASH_PIXEL_W;
    p_top = p_rect_.y + PLAYER_TRASH_PIXEL_Y;
    p_bottom = p_rect_.y + p_rect_.h - PLAYER_TRASH_PIXEL_H;

    a_left = acceleration_.GetAccelerate().at(pos_);
    a_right = acceleration_.GetAccelerate().at(pos_) + a_rect_.w;
    a_top = a_rect_.y;
    a_bottom = a_rect_.y + a_rect_.h;

    if (((p_bottom <= a_top) || (p_top >= a_bottom) || (p_right <= a_left) || (p_left >= a_right)) == false)
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

void Mechanism::DrawScore(Object &o_score_, Timer &o_timer_, SDL_Renderer *des, TTF_Font *font, SDL_Color color, int &time, float &acceleration, int &score)
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

void Mechanism::ChangeGameState(bool &play_, bool &is_running_, bool &is_lose_, Object &o_lose_game_, SDL_Renderer *des)
{
    is_running_ = false;
    is_lose_ = true;
    play_ = false;
    
    //o_lose_game_.RenderPos(150, 150, des);
}

void Mechanism::DrawLoseGame(SDL_Event &play_event_, bool &play_, bool &is_running_, bool &is_lose_, Object &o_lose_game_, SDL_Renderer *des)
{
    // if (play_)
    // {
    //     bool return_menu_ = false;
    //     while (!return_menu_)
    //     {
    //         while (SDL_PollEvent(&play_event_))
    //         {
    //             if (play_event_.type == SDL_QUIT)
    //             {
    //                 return_menu_ = true;
    //                 play_ = false;
    //                 break;
    //             }

    //             if (play_event_.type == SDL_MOUSEBUTTONDOWN)
    //             {

    //             }
    //         }
    //     }
    // }


    //o_lose_game_.Render(des);
    // SDL_Texture *new_Texture = nullptr;
    // SDL_Surface *load_surface = IMG_Load("res/menu/notification.png");
    // if (load_surface != nullptr)
    // {
    //     // Xóa những cái background đằng sau ảnh của character (transparent)
    //     //SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR));
    //     new_Texture = SDL_CreateTextureFromSurface(des, load_surface);
    //     if (new_Texture == nullptr)
    //     {
    //         cout << "Failed to create texture" << endl;
    //         // Surface dang luu thong so anh
    //     }

    //     SDL_FreeSurface(load_surface);
    // }
    // else 
    // {
    //     cout << "Failed to load lose image!" << endl;
    // }
    //SDL_RenderPresent(des);
    // SDL_RenderCopy(des, new_Texture, nullptr, nullptr);
    // SDL_DestroyTexture(new_Texture);
}