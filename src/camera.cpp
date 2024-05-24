#include "camera.hpp"
#include "config.hpp"
#include "player.hpp"
#include "transform.hpp"
#include <cmath>
#include <flecs.h>
#include <flecs/addons/cpp/mixins/pipeline/decl.hpp>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

static void move(const Position& p, const Head& h, Camera& c) {
  Vector3 dir = Vector3Normalize({sinf(h.y), 0.0f, cosf(h.y)});
  // The camera should be slightly infront of the player
  c.position = Vector3Add(p, Vector3Scale(dir, RELATIVE_CAMERA_FORWARD));
  // The camera should be at the player's head
  c.position.y += CAMERA_HEIGHT;
}

static void look(const Head& h, Camera& c) {
  Vector3 dir = {sinf(h.y) * cosf(h.x), sinf(h.x), cosf(h.y) * cosf(h.x)};
  c.target = Vector3Add(c.position, dir);
}

camera::camera(flecs::world& world) {
  world.set<Camera>({
    .up = {0.0f, 1.0f, 0.0f},
    .fovy = 45.0f,
    .projection = CAMERA_PERSPECTIVE,
  });

  world.system<const Position, const Head, Camera>()
    .kind(flecs::PostUpdate)
    .arg(1)
    .src<Player>()
    .arg(2)
    .src<Player>()
    .arg(3)
    .singleton()
    .each(move);

  world.system<const Head, Camera>()
    .kind(flecs::PostUpdate)
    .arg(1)
    .src<Player>()
    .arg(2)
    .singleton()
    .each(look);
}

}
