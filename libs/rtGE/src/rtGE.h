#pragma once
#include "../include/rtGE.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

struct GraphicLayer {
  bool isActive = true;

  virtual void preDraw() = 0;
  virtual void finalize() = 0;
};

SDL_Renderer* getRenderer();

void initGraphicLayers(int screenWidth, int screenHeight, bool motionBlurOn);

void save_texture(SDL_Texture* texture, std::string name);
SDL_Texture* get_texture(int texture_id);
int get_texture_id(std::string name);


