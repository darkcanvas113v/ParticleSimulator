#include "game.h"
#include "data/world.h"
#include "view/window.h"
#include <stdlib.h>
#include "view/def.h"
#include "utils.h"
#include <math.h>
#include <vector>
#include <stdio.h>
#include <quadtree.h>

void game::init_board(
  int numOfParticles,
  float temperature
) {
  world::init();

  quad_tree::init_quad(0, 0, SCREEN_WIDTH);

  int generation_attempts = 0;

  auto positions = std::vector<Vector2>(numOfParticles);

  auto vec = utils::split_number_in_random_intervals(numOfParticles, temperature * numOfParticles);
  for (int i = 0; i < numOfParticles; i++) {
    generation_attempts++;

    positions[i] = Vector2 {
      (float)(std::rand() % (SCREEN_WIDTH - 2*PARTICLE_SIZE) + PARTICLE_SIZE), 
      (float)(std::rand() % (SCREEN_HEIGHT - 2*PARTICLE_SIZE) + PARTICLE_SIZE)
    };

    bool validPos = true;

    for (int j = i-1; j > -1; j--) {
      if (positions[i].distSqrd(positions[j]) < PARTICLE_RADIUS_SQRD) {
        validPos = false;
        break;
      }
    }

    if (generation_attempts > numOfParticles + 1000) {
      printf("Generation of some particles failed! Looks like no space is avialable. Skipped %d particles", numOfParticles - i);
      break;
    }

    if (!validPos) {
      i = i - 1;
      continue;
    }

    float angle = utils::randomAngle();

    world::create_particle(positions[i], Vector2{vec[i]*cos(angle), vec[i]*sin(angle)});
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