#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

struct Look : Vector2 {};
struct Move : Vector2 {};
struct Input {
  int _;
};

struct input {
  input(flecs::world& world);
};

}
