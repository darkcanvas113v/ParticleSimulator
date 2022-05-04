#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "view/window.h"
#include "game.h"

void quit() {
  window::close();
}

const float physicsUpdateInterval = 1 / 60;
const float renderUpdateInterval = 1 / 60;

int main(int argc, char* args[]) {
  std::srand(time(0));

  if (window::init() == false) {
    return EXIT_FAILURE;
  }

  game::init_board(30, 50);

  Uint32 lastRenderUpdateTimeStamp = SDL_GetTicks();
  Uint32 lastPhysicsUpdateTimeStamp = SDL_GetTicks();
  float dt = 0;

  SDL_Event e;
  while(true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit();
        return 0;
      }
    }

    dt = (float)(SDL_GetTicks() - lastPhysicsUpdateTimeStamp) / 1000;
    if (dt > physicsUpdateInterval) {
      game::physics_loop(dt);
      lastPhysicsUpdateTimeStamp = SDL_GetTicks();
    }

    dt = (float)(SDL_GetTicks() - lastRenderUpdateTimeStamp) / 1000;
    if (dt > renderUpdateInterval) {
      window::draw();
      game::render_loop();
      window::update();
      lastRenderUpdateTimeStamp = SDL_GetTicks();
    }
  }

  return 0;
}