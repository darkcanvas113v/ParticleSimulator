#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"
#include <rtGE.h>
#include "game.h"
#include "view/def.h"

void quit() {
  rtGE::close();
}

const float physicsUpdateInterval = 1 / 60;
const float renderUpdateInterval = 1 / 60;
const float consoleUpdateInterval = 1;

int main(int argc, char* args[]) {
  std::srand(time(0));

  if (rtGE::init(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle simulator") == false) {
    return EXIT_FAILURE;
  }

  game::init_board(100, 20);

  Uint32 lastRenderUpdateTimeStamp = SDL_GetTicks();
  Uint32 lastPhysicsUpdateTimeStamp = SDL_GetTicks();
  Uint32 lastConsoleUpdateTimeStamp = SDL_GetTicks();
  float dt = 0;

  Uint64 physicsCalculationTime = 0;
  Uint64 renderTime = 0;

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
      auto timeStamp = SDL_GetPerformanceCounter();
      game::physics_loop(dt);
      lastPhysicsUpdateTimeStamp = SDL_GetTicks();
      physicsCalculationTime = SDL_GetPerformanceCounter() - timeStamp;
    }

    dt = (float)(SDL_GetTicks() - lastRenderUpdateTimeStamp) / 1000;
    if (dt > renderUpdateInterval) {
      auto timeStamp = SDL_GetPerformanceCounter();

      rtGE::draw();
      game::render_loop();
      rtGE::update();
      
      lastRenderUpdateTimeStamp = SDL_GetTicks();
      renderTime = SDL_GetPerformanceCounter() - timeStamp;
    }

    dt = (float)(SDL_GetTicks() - lastConsoleUpdateTimeStamp) / 1000;
    if (dt > consoleUpdateInterval) {
      system("clear");
      printf("Calculation time: %d\n", physicsCalculationTime);
      printf("Render time: %d\n", renderTime);
      lastConsoleUpdateTimeStamp = SDL_GetTicks();
    }
  }

  return 0;
}