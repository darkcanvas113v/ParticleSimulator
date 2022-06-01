#include "rtGE.h"

#include <stdexcept>
#include <unordered_map>

const static int MAX_TEXTURE_POOL_SIZE = 100;

SDL_Texture* pool[MAX_TEXTURE_POOL_SIZE];
std::unordered_map<std::string, int> name_to_id_map;

int size = 0;

void save_texture(SDL_Texture* texture, std::string name) {
  if (size == MAX_TEXTURE_POOL_SIZE) {
    throw std::overflow_error("Texture pool overflow!");
  }

  name_to_id_map[name] = size;
  pool[size] = texture;
}

SDL_Texture* get_texture(int texture_id) {
  return pool[texture_id];
}

int get_texture_id(std::string name) {
  return name_to_id_map[name];
}