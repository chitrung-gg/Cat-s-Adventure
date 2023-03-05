#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>

#include "Game.hpp"
#include "TextureManager.hpp"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 640;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

int main(int argc, char* args[]) {

    Uint32 frameStart;
    int frameTime;

    Game *game;
    game->init("Ganyu", WIDTH, HEIGHT, false);
    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    game->clean();
    return 0;
}