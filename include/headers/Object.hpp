//Load ảnh lên màn hình (lớp cơ sở)

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "CommonFunction.hpp"

class Object
{
    public:
        Object();
        ~Object();

        bool LoadImg (string path, SDL_Renderer *screen);
        bool LoadRenderedText (string textureText, TTF_Font *textFont, SDL_Color textColor, SDL_Renderer *screen);
        void Render (SDL_Renderer *des,  SDL_Rect *clip = nullptr);
        void RenderPos (int x, int y, SDL_Renderer *des, SDL_Rect *clip = nullptr);
        void Free();

        void SetRect(const int &x, const int &y);
    
        SDL_Rect GetRect();
        SDL_Texture *GetObject();


        int GetPosX();
        int GetPosY();
        int GetWidth();
        int GetHeight();

    protected:
        SDL_Texture *p_object_;          // Luu hinh anh
        SDL_Rect rect_;                 // Luu kich thuoc

};

#endif