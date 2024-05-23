#include "physics.hpp"
#include "transform.hpp"
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

// Move and spin update their respective transforms. Only sends update when
// there is a change that is not 0.

void move(flecs::entity e, const Velocity& v, Position& p) {
  if (!Vector3Equals(v, Vector3Zero())) {
    Vector3 np = Vector3Add(p, Vector3Scale(v, GetFrameTime()));
    e.set<Position>(Position(np));
  }
}

void spin(flecs::entity e, const AngularVelocity& v, Rotation& r) {
  if (!Vector3Equals(v, Vector3Zero())) {
    Vector3 nr = Vector3Add(r, Vector3Scale(v, GetFrameTime()));
    e.set<Rotation>(Rotation(nr));
  }
}

physics::physics(flecs::world& world) {
  world.system<const Velocity, Position>().each(move);
  world.system<const AngularVelocity, Rotation>().each(spin);
}

}
