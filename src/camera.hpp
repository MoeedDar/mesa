#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

using Camera = Camera3D;

struct camera {
  camera(flecs::world& world);
};

};
