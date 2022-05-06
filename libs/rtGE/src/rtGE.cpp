#include "rtGE.h"

SDL_Window* mWindow = NULL;
SDL_Renderer* renderer = NULL;

bool rtGE::init(
  int screenWidth,
  int screenHeight,
  char* label
) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  mWindow = SDL_CreateWindow(label, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

  if (mWindow == NULL) {
    printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void rtGE::draw() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}

void rtGE::draw_circle(
  float pos_x,
  float pos_y,
  float D
) {
  SDL_Rect rect = { (int)(pos_x - D / 2), (int)(pos_y - D / 2), (int)D, (int)D };
  SDL_SetRenderDrawColor(renderer, 0xAF, 0x2F, 0x2F, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}

void rtGE::update() {
  SDL_RenderPresent(renderer);
}

void rtGE::close() {
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}