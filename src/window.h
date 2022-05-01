#pragma once

#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Surface* screenSurface;

bool init();

void draw();

void update();

void close();