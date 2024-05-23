#include "player.hpp"
#include "config.hpp"
#include "input.hpp"
#include "physics.hpp"
#include "transform.hpp"
#include <raylib.h>
#include <raymath.h>

namespace mesa {

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

player::player(flecs::world& world) {
  world.entity<Player>()
    .set<Player>({})
    .set<Head>({})
    .set<Position>({0.0f, 0.0f, 0.0f})
    .set<Rotation>({0.0f, 0.0f, 0.0f})
    .set<Velocity>({0.0f, 0.0f, 0.0f})
    .set<AngularVelocity>({0.0f, 0.0f, 0.0f})
    .set<Model>(LoadModelFromMesh(GenMeshCube(1.0f, 2.0f, 1.0f)));

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
}

}
