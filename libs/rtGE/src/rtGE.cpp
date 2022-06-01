#include "rtGE.h"

const std::string RES_PATH = "resources/";
const std::string IMAGES_PATH = RES_PATH + "images/";

SDL_Window* mWindow = NULL;
SDL_Renderer* renderer = NULL;

SDL_Renderer* getRenderer() {
  return renderer;
}

bool rtGE::init(
  int screenWidth,
  int screenHeight,
  char* label,
  bool motionBlurOn
) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags))
  {
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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
  
  initGraphicLayers(screenWidth, screenHeight, motionBlurOn);

  return true;
}

void rtGE::close() {
  SDL_DestroyWindow(mWindow);
  IMG_Quit();
  SDL_Quit();
}

void rtGE::load_texture(std::string path) {
  SDL_Surface* image = IMG_Load((IMAGES_PATH + path).c_str());

  if (image == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
  }

  auto texture = SDL_CreateTextureFromSurface(renderer, image);
  if(texture == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
  }

  SDL_FreeSurface(image);

  save_texture(texture, path);
}

void rtGE::draw_sprite(const Sprite* sprite, float x, float y) {
  SDL_Rect rect;
  rect.x = x - sprite->origin_x;
  rect.y = y - sprite->origin_y;

  rect.w = sprite->w;
  rect.h = sprite->h;

  SDL_RenderCopy(renderer, get_texture(sprite->texture_id), NULL, &rect);
}

Sprite* rtGE::get_sprite(std::string name, float w, float h, float origin_x, float origin_y) {
  return new Sprite(get_texture_id(name), w, h, origin_x, origin_y);
}