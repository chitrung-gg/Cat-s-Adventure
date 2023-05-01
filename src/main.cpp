#include "CommonFunction.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Mechanism.hpp"
#include "Timer.hpp"
#include "Button.hpp"
#include "Menu.hpp"
#include "Health.hpp"
#include "Speed.hpp"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Color gTextColor = {97, 178, 181};
TTF_Font *gFont = nullptr;
Mix_Music *gMusic = nullptr;
Mix_Chunk *gJump = nullptr;
Mix_Chunk *gCollide = nullptr;
Mix_Chunk *gLose = nullptr;
Mix_Chunk *gSelect = nullptr;

Object gMenuImg;
Object gInformation;
Object gHighScoreImg;
Object gBackground[BACKGROUND_TYPE][BACKGROUND_LAYER];
Object gLoseGame;
Object gGround[BACKGROUND_TYPE];
Object gScore;
Object gHighScore;

Button gPlayButton;
Button gPauseButton;
Button gHighscoresButton;
Button gInformationButton;
Button gExitButton;
Button gReplayButton;
Button gMusicEnable;
Button gMusicDisable;
Button gReturnButton;

Player gCharacter;

Enemy gAir0(AIR_ENEMY_TYPE);
//Enemy gAir1(AIR_ENEMY_TYPE);
Enemy gGround0(GROUND_ENEMY_TYPE);
Enemy gGround1(GROUND_ENEMY_TYPE);

Health gHeart;
Speed gSpeed;

Timer gTimer;
Mechanism gMechanism;
Menu gMenu;

bool Init()             // khoi tao thong so cho moi truong SDL
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL could not initialize! " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))           // thiet lap che do ti le chat luong
        {
            cout << "Warning: Linear texture could not be enabled! " << endl;
        }

        gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            cout << "Window could not be created! " << SDL_GetError() << endl;
            return false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr)
            {
                cout << "Could not create renderer " << SDL_GetError() << endl;
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                int imgFlags = IMG_INIT_PNG;                    //check SDL_image
                if (!(IMG_Init(imgFlags) && imgFlags))
                {
                    cout << "Failed to initialize SDL_image! " << IMG_GetError();
                    return false;
                }

                if (TTF_Init() == -1)
                {
                    cout << "Failed to initialize TTF_Font! " << TTF_GetError();
                    return false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "Failed to initialize SDL_mixer! " << Mix_GetError();
                    return false;
                }
            }
        }
    }

    return true;
}

bool LoadMedia()
{
    if (!gMenuImg.LoadImg("res/menu/Cat's Adventure.png", gRenderer))
    {
        cout << "Failed to load menu image! " << endl;
        return false;
    }

    if (!gInformation.LoadImg("res/menu/Information.png", gRenderer))
    {
        cout << "Failed to load information! " << endl;
        return false;
    }

    if (!gHighScoreImg.LoadImg("res/menu/highscore.png", gRenderer))
    {
        cout << "Failed to load highscore bkg" << endl;
        return false;
    }  

    gMusic = Mix_LoadMUS("res/sound/Feeling_Happy.wav");
    if (gMusic == nullptr)
    {
        cout << "Failed to load music! " << endl;
        return false;
    }

    gJump = Mix_LoadWAV("res/sound/Jump.wav");
    if (gJump == nullptr)
    {
        cout << "Failed to load jump sound! " << endl;
        return false;
    }

    gLose = Mix_LoadWAV("res/sound/Lose.wav");
    if (gLose == nullptr)
    {
        cout << "Failed to load lose sound! " << endl;
        return false;
    }

    gSelect = Mix_LoadWAV("res/sound/Select.wav");
    if (gSelect == nullptr)
    {
        cout << "Failed to load select sount! " << endl;
        return false;
    }

    gCollide = Mix_LoadWAV("res/sound/Collide.wav");
    if (gCollide == nullptr)
    {
        cout << "Failed to load collide sound!" << endl;
        return false;
    }

    if (!gPlayButton.LoadImg("res/button/Play.png", gRenderer))
    {
        cout << "Failed to load play button! " << endl;
        return false;
    }

    if (!gHighscoresButton.LoadImg("res/button/Highscores.png", gRenderer))
    {
        cout << "Failed to load highscores button! " << endl;
        return false;
    }

    if (!gInformationButton.LoadImg("res/button/Information.png", gRenderer))
    {
        cout << "Failed to load information button" << endl;
        return false;
    }

    if (!gExitButton.LoadImg("res/button/Exit.png", gRenderer))
    {
        cout << "Failed to load exit button" << endl;
        return false;
    }

    if (!gReturnButton.LoadImg("res/button/Return.png", gRenderer))
    {
        cout << "Failed to load return button" << endl;
        return false;
    }

    if (!gHeart.LoadImg("res/heart/Heart.png", gRenderer))
    {
        cout << "Failed to load heart image" << endl;
        return false;
    }

    if (!gSpeed.LoadImg("res/acceleration/speed.png", gRenderer))
    {
        cout << "Failed to load speed image" << endl;
        return false;
    }

    else
    {
        if (!gLoseGame.LoadImg("res/menu/notification.png", gRenderer))
        {
            cout << "Failed to load lose image!" << endl;
            return false;
        }

        for (int i = 0; i < BACKGROUND_TYPE; i++)
        {
            for (int j = 0; j < BACKGROUND_LAYER; j++)
            {
                if (!gBackground[i][j].LoadImg(LAYER[i][j].c_str(), gRenderer))
                {
                    cout << "Failed to load background " << i << endl;
                    return false;
                }   
            }
            
        }

        for (int i = 0; i < BACKGROUND_TYPE; i++)
        {
            if (!gGround[i].LoadImg(LAYER_GROUND[i].c_str(), gRenderer))
            {
                cout << "Failed to load ground " << endl;
                return false;
            }
        }

        gFont = TTF_OpenFont("fonts/NiceSugar.ttf", 35);
        if (gFont == nullptr)
        {
            cout << "Failed to load font! " << endl;
            return false;
        }

        if (!gPauseButton.LoadImg("res/button/Pause.png",gRenderer))
        {
            cout << "Failed to load pause button! " << endl;
            return false;
        }

        if (!gReplayButton.LoadImg("res/button/Replay.png", gRenderer))
        {
            cout << "Failed to load replay button! " << endl;
            return false;
        }

        if (!gMusicEnable.LoadImg("res/button/Music_Enable.png", gRenderer))
        {
            cout << "Failed to load music_enable button" << endl;
            return false;
        }

        if (!gMusicDisable.LoadImg("res/button/Music_Disable.png", gRenderer))
        {
            cout << "Failed to load music_disable button" << endl;
            return false;
        }

        if (!gCharacter.LoadImg("res/cat/Run.png", gRenderer))
        {
            cout << "Failed to load cat image" << endl;
            return false;
        }

        if (!(gAir0.LoadImg("res/enemy/Helicopter.png", gRenderer) /*&& gAir1.LoadImg("res/enemy/Vulture.png", gRenderer)*/))
        {
            cout << "Failed to load air enemies" << endl;
            return false;
        }

        if (!(gGround0.LoadImg("res/enemy/Cactus.png", gRenderer) && gGround1.LoadImg("res/enemy/Mummy.png", gRenderer)))
        {
            cout << "Failed to load ground enemies" << endl;
            return false;
        }


        
    }

    return true;
}

void close()
{
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gLose);
    Mix_FreeChunk(gSelect);
    Mix_FreeChunk(gJump);
    Mix_FreeChunk(gCollide);
    gMusic = nullptr;
    gJump = nullptr;
    gSelect = nullptr;
    gLose = nullptr;
    gCollide = nullptr;

    gPlayButton.Free();
    gPauseButton.Free();
    gHighscoresButton.Free();
    gInformationButton.Free();
    gExitButton.Free();
    gReplayButton.Free();
    gMusicEnable.Free();
    gMusicDisable.Free();
    gReturnButton.Free();

    gCharacter.Free();

    gAir0.Free();
    //gAir1.Free();
    gGround0.Free();
    gGround1.Free();
    
    for (int i = 0; i < BACKGROUND_TYPE; i++)
    {
        for (int j = 0; j < BACKGROUND_LAYER; j++)
        {
            gBackground[i][j].Free();
        }
    }

    for (int i = 0; i < BACKGROUND_TYPE; i++)
    {
        gGround[i].Free();
    }
    gMenuImg.Free();
    gInformation.Free();
    gScore.Free();
    gHighScore.Free();
    gHeart.Free();
    gSpeed.Free();

    TTF_CloseFont(gFont);
    gFont = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();    
}

int main(int argc, char *argv[])
{
    if (!Init())
    {
        cout << "Failed to init data! " << endl;
        return -1;
    }
    
    if (!LoadMedia())
    {
        cout << "Failed to load images! " << endl;
        return -1;
    }

    srand(time(nullptr));
    bool is_quit_ = false;
    bool menu_quit_ = false;
    bool play_ = false;
    bool mute_ = false;
    bool end_lose_ = false;

    while (!is_quit_)
    {
        if (!mute_)
        {
            Mix_PlayMusic(gMusic, REPEAT_SOUND);
        }

        while (!menu_quit_)
        {
            SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(gRenderer);

            gMenuImg.Render(gRenderer);
            gPlayButton.SetPosition(PLAY_BUTTON_POS_X, PLAY_BUTTON_POS_Y);
            gHighscoresButton.SetPosition(HIGHSCORES_BUTTON_POS_X, HIGHSCORES_BUTTON_POS_Y);
            gMusicEnable.SetPosition(MUSIC_ENABLE_BUTTON_POS_X, MUSIC_ENABLE_BUTTON_POS_Y);
            gMusicDisable.SetPosition(MUSIC_DISABLE_BUTTON_POS_X, MUSIC_DISABLE_BUTTON_POS_Y);
            gInformationButton.SetPosition(INFORMATION_BUTTON_POS_X, INFORMATION_BUTTON_POS_Y);
            gExitButton.SetPosition(EXIT_BUTTON_POS_X, EXIT_BUTTON_POS_Y);
            gReturnButton.SetPosition(MENU_RETURN_BUTTON_POS_X, MENU_RETURN_BUTTON_POS_Y);

            SDL_Event menu_event_;

            while(SDL_PollEvent(&menu_event_))
            {
                if (menu_event_.type == SDL_QUIT)
                {
                    is_quit_ = true;
                    menu_quit_ = true;
                    play_ = false;
                    end_lose_ = true;
                }
                
                gMenu.RenderPlayButton(menu_event_, play_, menu_quit_, gPlayButton, gRenderer, gSelect);
                gMenu.RenderHighScoreButton(menu_event_, is_quit_, menu_quit_, play_, end_lose_, gReturnButton, gHighscoresButton, gHighScoreImg, gHighScore, gMechanism, gFont, gTextColor, gRenderer, gSelect);
                gMenu.RenderInformationButton(menu_event_, is_quit_, menu_quit_, play_, end_lose_, gReturnButton, gInformationButton, gInformation, gRenderer, gSelect);
                if (mute_)
                {
                    gMenu.RenderUnmuteButton(menu_event_, gMusicEnable, mute_, gRenderer, gSelect);
                }
                else
                {
                    gMenu.RenderMuteButton(menu_event_, gMusicDisable, mute_, gRenderer, gSelect); 
                }
                gMenu.RenderExitButton(menu_event_, is_quit_, menu_quit_, play_, end_lose_, gExitButton, gRenderer, gSelect);
            }

            gPlayButton.RenderButton(gRenderer);
            gHighscoresButton.RenderButton(gRenderer);
            
            if (mute_)
            {
                gMusicEnable.RenderButton(gRenderer);
                
            }
            else
            {
                gMusicDisable.RenderButton(gRenderer);
            }

            gInformationButton.RenderButton(gRenderer);
            gExitButton.RenderButton(gRenderer);

            SDL_RenderPresent(gRenderer);
        }

        while (play_)
        {
            SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(gRenderer);

            gPauseButton.SetPosition(PAUSE_BUTTON_POS_X, PAUSE_BUTTON_POS_Y);
            gPlayButton.SetPosition(PAUSE_BUTTON_POS_X, PAUSE_BUTTON_POS_Y);
            gMusicEnable.SetPosition(MUSIC_ENABLE_BUTTON_POS_X, MUSIC_ENABLE_BUTTON_POS_Y);
            gMusicDisable.SetPosition(MUSIC_DISABLE_BUTTON_POS_X, MUSIC_DISABLE_BUTTON_POS_Y);
            gReturnButton.SetPosition(GAME_RETURN_BUTTON_POS_X, GAME_RETURN_BUTTON_POS_Y);
            gReplayButton.SetPosition(REPLAY_BUTTON_POS_X, REPLAY_BUTTON_POS_Y);
            
            int time = 0, score = 0, speed = 0;
            float acceleration = 0;
            int num_collision = 0, cnt_collision = 0;
            int background_type = rand() % (BACKGROUND_TYPE);

            gTimer.Start();

            gCharacter.SetRect(PLAYER_POS_X, GROUND);

            gGround0.GenerateEnemy();
            gGround1.GenerateEnemy();
            gAir0.GenerateEnemy();
            //gAir1.GenerateEnemy();

            gHeart.Init(gRenderer);
            gSpeed.Init(gRenderer);

            SDL_Event play_event_;
            vector<float> speed_layer_(BACKGROUND_LAYER, INIT_SPEED);
            bool is_running_ = true, is_lose_ = false, is_paused_ = false;
            end_lose_ = false;

            while (is_running_)
            {
                while (SDL_PollEvent(&play_event_))
                {
                    if (play_event_.type == SDL_QUIT)
                    {
                        is_running_ = false;
                        is_quit_ = true;
                        play_ = false;
                        menu_quit_ = true;
                        end_lose_ = true;
                    }

                    if (mute_)
                    {
                        gMenu.RenderUnmuteButton(play_event_, gMusicEnable, mute_, gRenderer, gSelect);   
                    }
                    else
                    {
                        gMenu.RenderMuteButton(play_event_, gMusicDisable, mute_, gRenderer, gSelect);
                    }

                    if (!is_paused_)
                    {
                        gMenu.RenderPauseButton(play_event_, is_paused_, gPauseButton, gRenderer, gSelect);
                        gCharacter.HandleInputAction(play_event_, gJump);
                    }
                    
                    else
                    {
                        gTimer.Pause();
                        gMenu.RenderUnpauseButton(play_event_, is_paused_, gPlayButton, gRenderer, gSelect);

                        if ((gPlayButton.IsInside(play_event_)) && (play_event_.type == SDL_MOUSEBUTTONDOWN))
                        {
                            gTimer.Start();
                        }
                    }
                }

                if ((!is_lose_) && (!is_paused_))
                {
                    gMechanism.RenderScrollingBackground(speed_layer_, acceleration, gBackground[background_type], gRenderer);
                    gMechanism.RenderScrollingGround(speed, acceleration, gGround[background_type], gRenderer);

                    if (mute_)
                    {
                        gMusicEnable.RenderButton(gRenderer);
                    }
                    else
                    {
                        gMusicDisable.RenderButton(gRenderer);
                    }

                    gHeart.Show(gRenderer);
                    
                    gSpeed.Move(gRenderer);
                    gSpeed.Show(gRenderer);

                    gPauseButton.RenderButton(gRenderer);

                    gCharacter.DoPlayer();
                    gCharacter.Show(gRenderer);

                    gGround0.Move(acceleration);
                    gGround0.Show(gRenderer);

                    gGround1.Move(acceleration);
                    gGround1.Show(gRenderer);

                    gAir0.Move(acceleration);
                    gAir0.Show(gRenderer);

                    // gAir1.Move(acceleration);
                    // gAir1.Show(gRenderer);

                    gMechanism.DrawScore(gScore, gTimer, gRenderer, gFont, gTextColor, time, acceleration, score);
                    gMechanism.DrawHighScore(gHighScore, gRenderer, gFont, gTextColor);
                }

                if (is_paused_)
                {
                    if (mute_)
                    {
                        gMusicEnable.RenderButton(gRenderer);
                    }
                    else
                    {
                        gMusicDisable.RenderButton(gRenderer);
                    }
                 
                    gPlayButton.RenderButton(gRenderer);
                }

                for (int i = 0; i < gSpeed.GetAccelerate().size(); i++)
                {
                    if (gMechanism.CheckAccelerationCollision(gCharacter, gSpeed, i))
                    {
                        gSpeed.DecreaseAccelerate(acceleration, i);
                    }
                }
        
                if ((gMechanism.CheckCollision(gCharacter, gAir0) || gMechanism.CheckCollision(gCharacter, gGround0) /*|| gMechanism.CheckCollision(gCharacter, gAir1) */|| gMechanism.CheckCollision(gCharacter, gGround1)))
                {
                    if (!is_paused_) cnt_collision++;
                    
                    if (cnt_collision % 20 == 0) 
                    {
                        num_collision++;
                        if (num_collision <= 3)
                        {
                            Mix_PlayChannel(CHUNK_CHANNEL, gCollide, NOT_REPEAT_SOUND);
                            gHeart.DecreaseHeart();
                            gHeart.Show(gRenderer);
                        }

                        else 
                        {
                            gTimer.Pause();
                            if (!is_lose_)
                            {
                                Mix_PauseMusic();
                                Mix_PlayChannel(CHUNK_CHANNEL, gLose, NOT_REPEAT_SOUND);
                            }
                            gMechanism.UpdateHighScore(score, "res/highscore.txt");
                            gMechanism.ChangeGameState(play_, is_running_, is_lose_); 
                            break;
                        }
                        cnt_collision = 0;
                    }
                }
                SDL_RenderPresent(gRenderer);
                gMechanism.ControlFPS(gTimer);
            }
        }

        while (!end_lose_)
        {
            SDL_Event lose_event_;
            while (SDL_PollEvent(&lose_event_))
            {
                if (lose_event_.type == SDL_QUIT)
                {
                    is_quit_ = true;
                    end_lose_ = true;
                    menu_quit_ = true;
                    play_ = false;
                }

                if (mute_)
                {
                    gMenu.RenderUnmuteButton(lose_event_, gMusicEnable, mute_, gRenderer, gSelect);   
                }
                else
                {
                    gMenu.RenderMuteButton(lose_event_, gMusicDisable, mute_, gRenderer, gSelect);
                }
                
                gMenu.RenderReplayButton(lose_event_, gReplayButton, gReturnButton, menu_quit_, play_, end_lose_, gSelect);
            }

            gLoseGame.RenderPos(190, 100, gRenderer);
            gReturnButton.RenderButton(gRenderer);
            gReplayButton.RenderButton(gRenderer);
            
            SDL_RenderPresent(gRenderer);
        }
    }
    close();
    return 0;
}

