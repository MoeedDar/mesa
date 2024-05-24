#include "animation.hpp"
#include "graphics.hpp"
#include <flecs.h>
#include <raylib.h>

namespace mesa {

Animations::Animations(const char* path) {
  anims = LoadModelAnimations(path, &num_anims);
}

Animations::~Animations() {
  // UnloadModelAnimations(anims, num_anims);
}

void Animations::play(int anim) {
  this->anim = anim;
  frame = 0;
}

void Animations::reset() {
  play(-1);
}

void Animations::tick(Model model) {
  if (anim == -1 || anim > num_anims) {
    return;
  }
  frame += GetFrameTime() * 50;
  UpdateModelAnimation(model, anims[anim], static_cast<int>(frame));
  if (frame >= anims[anim].frameCount) {
    frame = 0;
  }
}

static void update(Animations& a, const Model& m) {
  a.tick(m);
}

animation::animation(flecs::world& world) {
  world.system<Animations, const Model>().each(update);
}

}