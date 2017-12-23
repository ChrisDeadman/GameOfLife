#ifndef GAMEOFLIFE_SDLUTIL_H
#define GAMEOFLIFE_SDLUTIL_H

#include <SDL.h>
#include <SDL_ttf.h>

void drawText(SDL_Renderer *renderer, int x, int y, TTF_Font *font, SDL_Color textColor, string text) {
    auto surface = TTF_RenderUTF8_Solid(font, text.c_str(), textColor);
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect{x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

#endif //GAMEOFLIFE_SDLUTIL_H
