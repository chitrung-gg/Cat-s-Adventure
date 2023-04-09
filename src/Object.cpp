#include "Object.hpp"

Object::Object()        //constructor
{
    p_object_ = nullptr;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

Object::~Object()       //deconstructor
{
    Free();
}

bool Object::LoadImg(string path, SDL_Renderer* screen)
{
    Free();

    SDL_Texture *new_Texture = nullptr;
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface != nullptr)
    {
        // Xóa những cái background đằng sau ảnh của character (transparent)
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR));
        new_Texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_Texture != nullptr)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
            // Surface dang luu thong so anh
        }

        SDL_FreeSurface(load_surface);
    }

    p_object_ = new_Texture;
    return (p_object_ != nullptr);

    // Sau khi goi xong se co mTexture va thong so width, height cua texture (kich thuoc)
}

bool Object::LoadRenderedText (string textureText, TTF_Font *textFont, SDL_Color textColor, SDL_Renderer *screen)
{
    Free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(textFont, textureText.c_str(), textColor);
    if (textSurface == nullptr)
    {
        cout << "Unable to render text surface! " << endl;
    }
    else
    {
        p_object_ = SDL_CreateTextureFromSurface(screen, textSurface);
        if (p_object_ == nullptr)
        {
            cout << "Unable to create texture from surface! " << endl;
        }
        else
        {
            rect_.w = textSurface->w;
            rect_.h = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return p_object_ != nullptr;
}

void Object::Render(SDL_Renderer *des, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};  // vi tri + kic thuoc anh
    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(des, p_object_, clip, &renderQuad);
    // day toan bo thong so mTexture vao gRenderer voi kich thuoc va vi tri la renderquad

}

void Object::RenderPos(int x, int y, SDL_Renderer *des, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x, y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, clip, &renderQuad);
}

void Object::Free()
{
    if (p_object_ != nullptr)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = nullptr;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void Object::SetRect(const int &x, const int &y)
{   
    rect_.x = x;
    rect_.y = y;
}

SDL_Rect Object::GetRect()
{
    return rect_;
}

SDL_Texture *Object::GetObject()
{
    return p_object_;
}

int Object::GetPosX()
{
    return rect_.x;
}

int Object::GetPosY()
{
    return rect_.y;
}

int Object::GetWidth()
{
    return rect_.w;
}

int Object::GetHeight()
{
    return rect_.h;
}