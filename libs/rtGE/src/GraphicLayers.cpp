#include "rtGE.h"

SDL_Texture* lastFrame;

struct DefaultLayer: public GraphicLayer {
  void preDraw() {
    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(getRenderer());
  }

  void finalize() {
    SDL_RenderPresent(getRenderer());
  }
} defaultLayer;

struct MotionBlurLayer: public GraphicLayer {
  void preDraw() {
    SDL_RenderCopy(getRenderer(), lastFrame, NULL, NULL);
  }

  void finalize() {
    unsigned char* pixels;
    int pitch;

    SDL_LockTexture(lastFrame, NULL, (void**)&pixels, &pitch);
    SDL_RenderReadPixels(getRenderer(), NULL, SDL_PIXELFORMAT_RGBA8888, pixels, pitch);
    SDL_UnlockTexture(lastFrame);

    SDL_SetTextureAlphaMod(lastFrame, 200);
  }
} motionBlurLayer;

const int MAX_LAYERS = 2;
GraphicLayer* preDrawQueue[MAX_LAYERS] = { &defaultLayer, &motionBlurLayer };
GraphicLayer* finalizeQueue[MAX_LAYERS] = { &motionBlurLayer, &defaultLayer };

void initGraphicLayers(int screenWidth, int screenHeight, bool motionBlurOn) {
  lastFrame = SDL_CreateTexture(getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
  if( lastFrame == NULL ) {
    printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
  }

  // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetTextureBlendMode(lastFrame, SDL_BLENDMODE_BLEND);

  motionBlurLayer.isActive = motionBlurOn;
}

void rtGE::draw() {
  for (int i = 0; i < MAX_LAYERS; i++) {
    auto layer = preDrawQueue[i];
    if (layer->isActive) layer->preDraw();
  }
}

void rtGE::update() {
  for (int i = 0; i < MAX_LAYERS; i++) {
    auto layer = finalizeQueue[i];
    if (layer->isActive) layer->finalize();
  }
}
