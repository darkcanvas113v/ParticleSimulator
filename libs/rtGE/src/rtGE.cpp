#include "rtGE.h"
#include "SDL2/SDL_image.h"
#include <stdexcept>
#include <unordered_map>

const std::string RES_PATH = "resources/";
const std::string IMAGES_PATH = RES_PATH + "images/";

const int MAX_TEXTURE_POOL_SIZE = 100;
struct TexturePool {
  SDL_Texture* pool[MAX_TEXTURE_POOL_SIZE];
  std::unordered_map<std::string, int> name_to_id_map;

  int size = 0;

  void put_texture(SDL_Texture* texture, std::string name) {
    if (size == MAX_TEXTURE_POOL_SIZE) {
      throw std::overflow_error("Texture pool overflow!");
    }

    name_to_id_map[name] = size;
    pool[size] = texture;
  }

  SDL_Texture* get_texture(int texture_id) {
    return pool[texture_id];
  }

  int get_texture_id(std::string name) {
    return name_to_id_map[name];
  }
};

SDL_Window* mWindow = NULL;
SDL_Renderer* renderer = NULL;

TexturePool texturePool;

SDL_Texture* lastFrame;

bool rtGE::init(
  int screenWidth,
  int screenHeight,
  char* label
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
  
  lastFrame = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
  if( lastFrame == NULL ) {
      printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
  }

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetTextureBlendMode(lastFrame, SDL_BLENDMODE_BLEND);

  return true;
}

void rtGE::draw() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, lastFrame, NULL, NULL);
}

void rtGE::update() {
  unsigned char* pixels;
  int pitch;

  SDL_LockTexture(lastFrame, NULL, (void**)&pixels, &pitch);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, pixels, pitch);
  SDL_UnlockTexture(lastFrame);

  SDL_RenderPresent(renderer);

  SDL_SetTextureAlphaMod(lastFrame, 200);
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

  texturePool.put_texture(texture, path);
}

void rtGE::draw_sprite(const Sprite* sprite, float x, float y) {
  SDL_Rect rect;
  rect.x = x - sprite->origin_x;
  rect.y = y - sprite->origin_y;

  rect.w = sprite->w;
  rect.h = sprite->h;

  SDL_RenderCopy(renderer, texturePool.get_texture(sprite->texture_id), NULL, &rect);
}

Sprite* rtGE::get_sprite(std::string name, float w, float h, float origin_x, float origin_y) {
  return new Sprite(texturePool.get_texture_id(name), w, h, origin_x, origin_y);
}