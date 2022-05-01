#include "window.h"
#include "def.h"

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  window = SDL_CreateWindow("Particle Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  screenSurface = SDL_GetWindowSurface(window);
  return true;
}

void draw() {
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
}

void update() {
  SDL_UpdateWindowSurface(window);
}

void close() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}