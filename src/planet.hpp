#pragma once

#include <flecs.h>
#include <vector>

namespace mesa {

struct Terrain {
  // Although this is a 1D array, it represents a 3D sphere representing the
  // terrain
  std::vector<float> scalar_field;
};

struct Planet {
  int _;
};

struct planet {
  planet(flecs::world& world);
};

}
