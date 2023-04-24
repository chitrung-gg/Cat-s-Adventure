#ifndef MENU_HPP_
#define MENU_HPP_

#include "CommonFunction.hpp"
#include "Object.hpp"
#include "Button.hpp"
#include "Mechanism.hpp"

/*
-mảng sdl rect 
- set các vị trí của sdl rect
- Kiẻu dữ liệu button gồm tất 
- Vòng trong loop của main menu
+ Load background dằng sau
+ Gọi button (Loadimg)
+  Vòng lặp sự kiện 
.switch (event.type)
..case SDL_Quit
..case SDL_MouseMotion (inside true thì render khác)
- dùng menu trước while (is_quit)
- SDL_RenderPresent thay thees SDL_Flip

*/

class Menu
{
    public:
        Menu();
        ~Menu();

        void RenderPlayButton(SDL_Event &event, bool &play_, bool &menu_quit_, Button &play_button_, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderPauseButton(SDL_Event &event, bool &is_pause_, Button &pause_button_, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderUnpauseButton(SDL_Event &event, bool &is_pause_, Button &play_button_, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderExitButton(SDL_Event &event, bool &is_quit_, bool &menu_quit_, bool &play_, bool &end_lose_, Button &exit_button_, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderInformationButton(SDL_Event &event, bool &is_quit_, bool &menu_quit_, bool &play_, bool &end_lose_, Button &return_button_, Button &information_button_, Object &information_menu_, /*Object &information_sheet_*/ SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderHighScoreButton(SDL_Event &event, bool &is_quit_, bool &menu_quit_, bool &play_, bool &end_lose_, Button &return_button_, Button &highscore_button_, Object &highscore_bkg_, Object &highscore_text_, Mechanism mechanism_, TTF_Font *font, SDL_Color textColor, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderMuteButton(SDL_Event &event, Button &mute_button_, bool &mute_, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderUnmuteButton(SDL_Event &event, Button &unmute_button_, bool &mute_, SDL_Renderer *des, Mix_Chunk *click_wav_);
        void RenderReplayButton(SDL_Event &event, Button &replay_button_, Button &return_button_, bool &menu_quit_, bool &play_, bool &end_lose_, Mix_Chunk *click_wav_);

    private:

};

#endif