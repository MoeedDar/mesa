#pragma once

#include <flecs.h>
#include <raylib.h>

namespace mesa {

struct Animations {
  Animations() = default;
  Animations(const char* file);
  ~Animations();

  ModelAnimation* anims;
  int num_anims;
  int anim = -1;
  float frame;

  void play(int anim);
  void reset();
  void tick(Model model);
};

struct animation {
  animation(flecs::world& world);
};

}