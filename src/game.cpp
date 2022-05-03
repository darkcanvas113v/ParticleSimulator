#include "game.h"
#include "data/world.h"
#include "view/window.h"
#include <stdlib.h>
#include "view/def.h"

void game::init_board(
  int numOfParticles,
  float temperature
) {
  world::init();
  for (int i = 0; i < numOfParticles; i++) {
    float pos_x = std::rand() % (SCREEN_WIDTH - 2*PARTICLE_SIZE) + PARTICLE_SIZE;
    float pos_y = std::rand() % (SCREEN_WIDTH - 2*PARTICLE_SIZE) + PARTICLE_SIZE;

    world::create_particle(pos_x, pos_y, 0, 0);
  }
}

void game::clear_board() {
  world::clear();
}

void game::physics_loop(float dt) {
  world::progress(dt);
}

void game::render_loop() {
  auto renderables = world::get_renderable_entities();

  renderables.each([](flecs::entity e, Position& p, Render r) {
    window::draw_circle(p.x, p.y);
  });
}