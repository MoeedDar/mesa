#include "camera.hpp"
#include "player.hpp"
#include "transform.hpp"
#include <cmath>
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

static void move(const Position& p, Camera& c) {
  c.position = p;
  c.position.y += 2;
}

static void look(const Head& h, Camera& c) {
  Vector3 dir = {
    sinf(h.y) * cosf(h.x),
    sinf(h.x),
    cosf(h.y) * cosf(h.x),
  };
  c.target = Vector3Add(c.position, dir);
}

camera::camera(flecs::world& world) {
  world.set<Camera>({
    .position = {0.0f, 5.0f, -5.0f},
    .target = {0.0f, 0.0f, 0.0f},
    .up = {0.0f, 1.0f, 0.0f},
    .fovy = 45.0f,
    .projection = CAMERA_PERSPECTIVE,
  });

  world.system<const Position, Camera>()
    .arg(1)
    .src<Player>()
    .arg(2)
    .singleton()
    .each(move);

  world.system<const Head, Camera>()
    .arg(1)
    .src<Player>()
    .arg(2)
    .singleton()
    .each(look);
}

}
