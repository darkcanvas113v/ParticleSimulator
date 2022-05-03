#include "game.h"
#include "data/world.h"
#include "view/window.h"
#include <stdlib.h>
#include "view/def.h"
#include "utils.h"
#include <math.h>

void game::init_board(
  int numOfParticles,
  float temperature
) {
  world::init();

  auto vec = utils::split_number_in_random_intervals(numOfParticles, temperature * numOfParticles);
  for (int i = 0; i < numOfParticles; i++) {
    float pos_x = std::rand() % (SCREEN_WIDTH - 2*PARTICLE_SIZE) + PARTICLE_SIZE;
    float pos_y = std::rand() % (SCREEN_WIDTH - 2*PARTICLE_SIZE) + PARTICLE_SIZE;

    float angle = utils::randomAngle();

    world::create_particle(Vector2{pos_x, pos_y}, Vector2{vec[i]*cos(angle), vec[i]*sin(angle)});
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
    window::draw_circle(p.current.x, p.current.y);
  });
}