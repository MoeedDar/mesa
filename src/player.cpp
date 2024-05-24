#include "player.hpp"
#include "animation.hpp"
#include "config.hpp"
#include "input.hpp"
#include "physics.hpp"
#include "transform.hpp"
#include <raylib.h>
#include <raymath.h>

namespace mesa {

enum class PlayerAnimation {
  Idle = 2,
  MoveForward = 4,
  MoveBackward = 7,
  MoveLeft = 3,
  MoveRight = 2,
  TurnLeft = 9,
  TurnRight = 8,
};

static void move(const Move& m, const Rotation& r, Velocity& v) {
  auto dir = Vector3RotateByAxisAngle(
    Vector3Normalize({m.x, 0, m.y}), {0.0f, 1.0f, 0.0f}, r.y
  );
  v = Velocity(Vector3Scale(dir, PLAYER_VELOCITY));
}

static void spin(const Look& l, AngularVelocity& v) {
  v.y = -l.x * MOUSE_SENSITIVITY;
}

static void look(const Look& l, const Rotation& r, Head& h) {
  h.y = r.y;
  h.x -= l.y * MOUSE_SENSITIVITY * GetFrameTime();
  h.x = Clamp(h.x, -PI / 2.0f, PI / 2.0f);
}

static void animate(const Velocity& v, Animations& a) {
  PlayerAnimation anim = PlayerAnimation::Idle;
  if (!Vector3Equals(v, Vector3Zero())) {
  }
  if (a.anim != int(anim)) {
    a.play(int(anim));
  }
}

static Scale calculate_player_scale(Model model) {
  const BoundingBox bbox = GetModelBoundingBox(model);
  const float height = bbox.max.y - bbox.min.y;
  const float factor = PLAYER_HEIGHT / height;
  return {factor, factor, factor};
}

player::player(flecs::world& world) {
  Model model = LoadModel("./assets/Character.m3d");
  Animations anims = Animations("./assets/Character.m3d");
  Scale scale = calculate_player_scale(model);

  world.entity<Player>()
    .set<Player>({})
    .set<Head>({})
    .set<Position>({0.0f, 0.0f, 0.0f})
    .set<Rotation>({0.0f, 0.0f, 0.0f})
    .set<Scale>(scale)
    .set<Velocity>({0.0f, 0.0f, 0.0f})
    .set<AngularVelocity>({0.0f, 0.0f, 0.0f})
    .set<Model>(model)
    .set<Animations>(anims);

  world.system<const Move, const Rotation, Velocity>()
    .arg(2)
    .src<Player>()
    .arg(3)
    .src<Player>()
    .each(move);

  world.system<const Look, AngularVelocity>().arg(2).src<Player>().each(spin);

  world.system<const Look, const Rotation, Head>()
    .arg(2)
    .src<Player>()
    .arg(3)
    .src<Player>()
    .each(look);

  world.system<const Velocity, Animations>()
    .arg(1)
    .src<Player>()
    .arg(2)
    .src<Player>()
    .each(animate);
}

}
