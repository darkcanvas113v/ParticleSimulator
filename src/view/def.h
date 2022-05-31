#pragma once

#include <rtmath.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int PARTICLE_SIZE = 4;
const int PARTICLE_RADIUS = PARTICLE_SIZE / 2;
const int PARTICLE_RADIUS_SQRD = PARTICLE_RADIUS * PARTICLE_RADIUS;

const Vector2 PLANET_POSITION { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

const int PLANET_SIZE = 50;
const int PLANET_RADIUS = PLANET_SIZE / 2;
const int PLANET_RADIUS_SQRD = PLANET_RADIUS * PLANET_RADIUS;

const int PLAN_PART_RADIUS_SUM = PLANET_RADIUS + PARTICLE_RADIUS;
const int PLAN_PART_RADIUS_SUM_SQRD = PLAN_PART_RADIUS_SUM * PLAN_PART_RADIUS_SUM;

const int PARTICLE_COLLISION_AREA_SQRD = PARTICLE_RADIUS_SQRD / 2;
