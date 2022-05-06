#include "quadtree.h"
#include <math.h>
#include <stdexcept>

const int QUAD_POOL_MAX_SIZE = 100;

const int NUM_OF_ENTITY_STORES = 50;
const int MAX_ENTITIES_PER_QUAD = 1000;

struct EntityStoreResult {
  Entity* result;
  int index;
};

struct EntityStore {
  bool available[NUM_OF_ENTITY_STORES];
  Entity entities[NUM_OF_ENTITY_STORES * 4 * MAX_ENTITIES_PER_QUAD];

  EntityStore() {
    for (int i = 0; i < NUM_OF_ENTITY_STORES; i++) {
      available[i] = true;
    }
  }

  EntityStoreResult get() {
    for (int i = 0; i < NUM_OF_ENTITY_STORES; i++) {
      if (available[i]) {
        available[i] = false;
        return EntityStoreResult {&entities[i * 4 * MAX_ENTITIES_PER_QUAD], i};
      }
    }
    throw std::overflow_error("No entity store is available!");
  }

  void free(int i) {
    available[i] = true;
  }
};

EntityStore entity_store;

const int ENTITY_BUFFER_SIZE = 1000;
Entity entity_buffer[ENTITY_BUFFER_SIZE];
int buffer_i = 0;

Quad quad_pool[QUAD_POOL_MAX_SIZE];
int quad_pool_last_free = QUAD_POOL_MAX_SIZE - 1;

Quad rootQuad;

void initialize_quad(Quad& q, float x, float y, float w) {
  q.x = x;
  q.y = y;
  q.w = w;
  q.divided = false;
  q.count = 0;
  q.rect = Rect {x - w, y - w, 2*w, 2*w};
}

int quad_i_by_pos(float x, float y) {
  int sx = signbit(x) ? 0 : 1;
  int sy = signbit(y) ? 0 : 1;
  return 3 - sx * 2 - sy;
}

int calculate_entity_loc_pos(Entity& e, float x, float y) {
  e.loc_x = e.x - x;
  e.loc_y = e.y - y;

  e.quad_id = quad_i_by_pos(e.loc_x, e.loc_y);
  return e.quad_id;
}

Quad* get_quad(float x, float y, float w) {
  if (quad_pool_last_free < 0) throw std::overflow_error("Quad pool overflow!");

  initialize_quad(quad_pool[quad_pool_last_free], x, y, w);
  auto quad = &quad_pool[quad_pool_last_free];
  quad_pool_last_free--;
  return quad;
}

Quad::Quad(float x, float y, float w) {
  initialize_quad(*this, x, y, w);
}

void Quad::insert(EntityIterator entities) {
  if (!divided && entities.size <= MAX_CHILDREN) {
    for (Entity* p = entities.start; p < entities.end; p++) {
      childrens[count++] = *p;
    }
    return;
  }

  divided = true;

  int quad_count[4] = {0, 0, 0, 0};

  quads[0] = get_quad(this->x + w / 2, this->y + w / 2, w / 2);
  quads[1] = get_quad(this->x + w / 2, this->y - w / 2, w / 2);
  quads[2] = get_quad(this->x - w / 2, this->y + w / 2, w / 2);
  quads[3] = get_quad(this->x - w / 2, this->y - w / 2, w / 2);

  EntityStoreResult store_result = entity_store.get();
  Entity* store = store_result.result;

  for (Entity* p = entities.start; p != entities.end; p++) {
    calculate_entity_loc_pos(*p, x, y);
    store[p->quad_id * MAX_ENTITIES_PER_QUAD + quad_count[p->quad_id]++] = *p;
  }

  for (int i = 0; i < 4; i++) {
    Entity* start = &store[i*MAX_ENTITIES_PER_QUAD];
    quads[i]->insert(EntityIterator {start, start + quad_count[i]});
  }

  entity_store.free(store_result.index);
}

void Quad::add_childrens_at_to_buffer(Rect r) {
  if (divided) {
    for (int i = 0; i < 4; i++) {
      if (quads[i]->rect.overlaps(r)) {
        quads[i]->add_childrens_at_to_buffer(r);
      }
    }
    return;
  }
  for (int i = 0; i < count; i++) {
    entity_buffer[buffer_i++] = childrens[i];
  }
}

void quad_tree::init_quad(float x, float y, float w) {
  initialize_quad(rootQuad, x + w/2, y + w/2, w/2);
}

void quad_tree::reset() {
  quad_pool_last_free = QUAD_POOL_MAX_SIZE - 1;
  buffer_i = 0;
  rootQuad.divided = false;
  rootQuad.count = 0;
}

void quad_tree::insert(const Entity& entity) {
  entity_buffer[buffer_i++] = entity;
}

void quad_tree::build() {
  rootQuad.insert(EntityIterator {entity_buffer, entity_buffer + buffer_i});
}

EntityIterator quad_tree::get_childrens_at(Rect r) {
  buffer_i = 0;
  rootQuad.add_childrens_at_to_buffer(r);
  return EntityIterator {entity_buffer, entity_buffer + buffer_i};
}