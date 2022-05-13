#include "../include/rtmath.h"

int round_up(float val) {
  return (int) val + 1;
}

int cap_low(int val, int low) {
  if (val < low) return low;
  return val;
}

int cap_up(int val, int up) {
  if (val > up) return up;
  return val;
}