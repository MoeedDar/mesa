#include "input.hpp"
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

static void handle_move(flecs::entity e, Move& m) {
  m.x = IsKeyDown(KEY_A) - IsKeyDown(KEY_D);
  m.y = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
  if (!Vector2Equals(m, Vector2Zero())) {
    e.modified<Move>();
  }
}

static void handle_look(flecs::entity e, Look& l) {
  l = std::bit_cast<Look, Vector2>(GetMouseDelta());
  if (!Vector2Equals(l, Vector2Zero())) {
    e.modified<Look>();
  }
}

input::input(flecs::world& world) {
  world.entity<Input>().set<Input>({}).set<Move>({}).set<Look>({});

  world.system<Move>().each(handle_move);
  world.system<Look>().each(handle_look);
}

}
