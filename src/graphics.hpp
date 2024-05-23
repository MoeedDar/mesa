#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

using Model = Model;

// This tag indicates whether a model should clean up it's own mesh. Useful for
// spawning multiple models with the same mesh
struct SharedMesh {};

struct graphics {
  graphics(flecs::world& world);
};

}
