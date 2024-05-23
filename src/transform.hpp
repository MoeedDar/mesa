#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

struct Transform : Matrix {};
struct Position : Vector3 {};
struct Rotation : Vector3 {};
struct Scale : Vector3 {};

struct transform {
  transform(flecs::world& world);
};

}
