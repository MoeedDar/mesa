#include "transform.hpp"
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

static void add_transform(flecs::entity e) {
  e.set<Transform>(Transform(MatrixIdentity()));
}

static void remove_transform(flecs::entity e) {
  e.remove<Transform>();
}

static void update_transform(flecs::entity e) {
  // Check if the entity contains transform vectors, or use a default
  const Vector3 p =
    e.has<Position>() ? Vector3(*e.get<Position>()) : Vector3Zero();
  const Vector3 r =
    e.has<Rotation>() ? Vector3(*e.get<Rotation>()) : Vector3Zero();
  const Vector3 s = e.has<Scale>() ? Vector3(*e.get<Scale>()) : Vector3One();

  // Get matrices for each transform
  const Matrix tm = MatrixTranslate(p.x, p.y, p.z);
  const Matrix rm = MatrixRotateXYZ(r);
  const Matrix sm = MatrixScale(s.x, s.y, s.z);

  // Propogate changes
  e.set(Transform(MatrixMultiply(rm, MatrixMultiply(sm, tm))));
}

template <typename T>
static constexpr void observe_transform_on_add(flecs::world& world) {
  world.observer()
    .with<T>()
    .template without<Transform>()
    .event(flecs::OnAdd)
    .each(add_transform);
}

transform::transform(flecs::world& world) {
  auto transforms = world.prefab().add<Position>().add<Rotation>().add<Scale>();

  // Scans whenever a transform component gets added. If so and the entity does
  // not have transform already, we add it
  observe_transform_on_add<Position>(world);
  observe_transform_on_add<Rotation>(world);
  observe_transform_on_add<Scale>(world);
  // Scans all transform components without the prefab components for deletion
  world.system()
    .with<Transform>()
    .term(transforms)
    .not_from()
    .each(remove_transform);

  // When any of the transform components change, we update transform
  world.observer()
    .term(transforms)
    .or_from()
    .event(flecs::OnSet)
    .each(update_transform);
}

};
