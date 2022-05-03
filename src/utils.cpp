#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>

const float PI = M_PI;

std::vector<float> utils::split_number_in_random_intervals(int size, float total_value, int precision) {
  std::vector<float> vec(size);

  int sum = 0;
  for (int i = 0; i < size; i++) {
    vec[i] = std::rand() % precision;
    sum += vec[i];
  }

  float scale = total_value / sum;

  for (int i = 0; i < size; i++) {
    vec[i] *= scale;
  }

  return vec;
}

float utils::randomAngle() {
  return PI * ((float)rand() / RAND_MAX);
}

