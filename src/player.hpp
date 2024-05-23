#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

struct Player {
  int _;
};

struct Head : Vector3 {};

struct player {
  player(flecs::world& world);
};

}
