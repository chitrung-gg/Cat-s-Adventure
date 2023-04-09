#include "Menu.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::RenderPlayButton(SDL_Event &event, bool &play_, bool &menu_quit_, Button &play_button_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (play_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP:
        {
            play_button_.SetMouseState(HOVER);            
            break;
        } 
        case SDL_MOUSEBUTTONDOWN:
        {
            play_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            play_ = true;
            menu_quit_ = true;
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        play_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderPauseButton(SDL_Event &event, bool &is_pause_, Button &pause_button_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (pause_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP: 
        {
            pause_button_.SetMouseState(HOVER);            
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            pause_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            is_pause_ = true;
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        pause_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderUnpauseButton(SDL_Event &event, bool &is_pause_, Button &play_button_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (play_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP: 
        {
            play_button_.SetMouseState(HOVER);            
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            play_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            is_pause_ = false;
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        play_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderExitButton(SDL_Event &event, bool &is_quit_, bool &menu_quit_, Button &exit_button_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (exit_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP:
        {
            exit_button_.SetMouseState(HOVER);            
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            exit_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            is_quit_ = true;
            menu_quit_ = true;
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        exit_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderInformationButton(SDL_Event &event, bool &is_quit_, bool &menu_quit_, Button &return_button_, Button &information_button_, Object &information_menu_, /*Object &information_sheet_*/ SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (information_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP: 
        {
            information_button_.SetMouseState(HOVER);            
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            information_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            bool information_ = false;

            while (!information_)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        information_ = true;
                        is_quit_ = true;
                        menu_quit_ = true;
                        return;
                    }   

                    if (return_button_.IsInside(event))
                    {
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP :
                            return_button_.SetMouseState(HOVER);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            return_button_.SetMouseState(CLICK);
                            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
                            information_ = true;
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        return_button_.SetMouseState(NORMAL);
                    }
                }
                
                information_menu_.RenderPos(188, 185, des);
                return_button_.RenderButton(des);

                SDL_RenderPresent(des);
            }
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        information_button_.SetMouseState(NORMAL);
    }
}


void Menu::RenderHighScoreButton(SDL_Event &event, bool &is_quit_, bool &menu_quit_, Button &return_button_, Button &highscore_button_, Object &highscore_bkg_, Object &highscore_text_, Mechanism mechanism_, TTF_Font *font, SDL_Color textColor, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (highscore_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP: 
        {
            highscore_button_.SetMouseState(HOVER);            
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            highscore_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            bool highscore_ = false;

            while (!highscore_)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        highscore_ = true;
                        is_quit_ = true;
                        menu_quit_ = true;
                        return;
                    }
                    
                    if (return_button_.IsInside(event))
                    {
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP :
                            return_button_.SetMouseState(HOVER);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            return_button_.SetMouseState(CLICK);
                            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
                            highscore_ = true;
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        return_button_.SetMouseState(NORMAL);
                    }
                }
                
                highscore_bkg_.RenderPos(200, 185, des);
                highscore_text_.LoadRenderedText(mechanism_.GetHighScore("res/highscore.txt"), font, textColor, des);
                highscore_text_.RenderPos(500, 300, des);
                return_button_.RenderButton(des);

                SDL_RenderPresent(des);
            }
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        highscore_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderMuteButton(SDL_Event &event, Button &mute_button_, bool &mute_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (mute_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP:
        {
            mute_button_.SetMouseState(HOVER);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            mute_button_.SetMouseState(CLICK);
            mute_ = true;
            if (!mute_) 
            {
                Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            }
            Mix_PauseMusic();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        mute_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderUnmuteButton(SDL_Event &event, Button &unmute_button_, bool &mute_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    if (unmute_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP:
        {
            unmute_button_.SetMouseState(HOVER);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            unmute_button_.SetMouseState(CLICK);
            mute_ = false;
            if (!mute_)
            {
                Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            }
            Mix_ResumeMusic();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        unmute_button_.SetMouseState(NORMAL);
    }
}

void Menu::RenderReplayButton(SDL_Event &event, Button &replay_button_, Button &return_button_, bool &menu_quit_, bool &play_, bool &is_paused_, bool &is_running_, Object &o_notification_, SDL_Renderer *des, Mix_Chunk *click_wav_)
{
    o_notification_.RenderPos(200, 185, des);

    if (return_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP: 
        {
            return_button_.SetMouseState(HOVER);            
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            return_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            menu_quit_ = false;
            play_ = false;
            is_paused_ = false;
            is_running_ = false;
            break;
        }
        default:
            break;
        }
    }
    else 
    {
        return_button_.SetMouseState(NORMAL);
    }

    if (replay_button_.IsInside(event))
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONUP :
        {
            replay_button_.SetMouseState(HOVER);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            replay_button_.SetMouseState(CLICK);
            Mix_PlayChannel(CHUNK_CHANNEL, click_wav_, NOT_REPEAT_SOUND);
            play_ = false;
            is_paused_ = false;
            menu_quit_ = false;
            break;
        }
        default:
            break;
        }
    }
    else
    {
        replay_button_.SetMouseState(NORMAL);
    }
}