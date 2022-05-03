#include "window.h"
#include "def.h"

SDL_Window* mWindow = NULL;
SDL_Renderer* renderer = NULL;

bool window::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  mWindow = SDL_CreateWindow("Particle Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

void window::draw() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}

void window::draw_circle(
  float pos_x,
  float pos_y
) {
  SDL_Rect rect = { pos_x - PARTICLE_SIZE / 2, pos_y - PARTICLE_SIZE / 2, PARTICLE_SIZE, PARTICLE_SIZE };
  SDL_SetRenderDrawColor(renderer, 0xAF, 0x2F, 0x2F, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}

void window::update() {
  SDL_RenderPresent(renderer);
}

void window::close() {
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}