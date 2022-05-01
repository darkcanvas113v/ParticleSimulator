#include "stdio.h"
#include "SDL2/SDL.h"
#include "window.h"
#include "string"

void quit() {
  close();
}

int main(int argc, char* args[]) {
  if (init() == false) {
    return EXIT_FAILURE;
  }

  SDL_Event e;
  while(true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit();
        return 0;
      }
    }
    draw();
    update();
  }

  return 0;
}