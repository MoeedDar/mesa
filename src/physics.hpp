#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

struct Velocity : Vector3 {};
struct AngularVelocity : Vector3 {};

struct physics {
  physics(flecs::world& world);
};

}
