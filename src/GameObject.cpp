#include "GameObject.hpp"
#include "TextureManager.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
using namespace std;

GameObject::GameObject(const char* texturesheet, int x, int y) {

    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

void GameObject::Update() 
{
    xpos++;
    ypos++;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = 32;
    srcRect.w = 32;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = srcRect.h * 2;
    destRect.w = srcRect.w * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}