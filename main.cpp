#include <bit>
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

struct Transform : Matrix {};
struct Position : Vector3 {};
struct Rotation : Vector3 {};
struct Scale : Vector3 {};

struct Player {
  int _;
};

static void update_transform(
  flecs::entity e, Transform& t, const Position* p, const Rotation* r,
  const Scale* s
) {
  // Check if the entity contains transform vectors, or use a default
  const Vector3 pos = p ? *static_cast<const Vector3*>(p) : Vector3Zero();
  const Vector3 rot = r ? *static_cast<const Vector3*>(p) : Vector3Zero();
  const Vector3 sca = s ? *static_cast<const Vector3*>(p) : Vector3One();
  //
  // Get matrices for each individual transform
  const Matrix tm = MatrixTranslate(pos.x, pos.y, pos.z);
  const Matrix rm = MatrixRotateXYZ(rot);
  const Matrix sm = MatrixScale(sca.x, sca.y, sca.z);
  // Multiply the transforms to get the final transformation matrix
  t = std::bit_cast<Transform>(MatrixMultiply(tm, MatrixMultiply(rm, sm)));

  printf("UPDATING TRANSFORM");

  // The propogation crashes it
  e.modified<Transform>();
}

static void render(const Model& m) {
  DrawModel(m, Vector3Zero(), 1, RAYWHITE);
}

static void pre_render(const Camera& c) {
  BeginDrawing();
  ClearBackground(BLACK);
  BeginMode3D(c);
}

static void post_render(flecs::iter& it) {
  EndMode3D();
  EndDrawing();
}

static void remove_model(Model& m) {
  UnloadModel(m);
}

static void update_model(Model& m, const Transform& t) {
  printf("UPDATING MODEL");
  m.transform = t;
}

}

int main() {
  using namespace mesa;

  InitWindow(400, 400, "test");

  flecs::world world;

  world
    .observer<mesa::Transform, const Position*, const Rotation*, const Scale*>()
    .event(flecs::OnSet)
    .each(update_transform);

  world.system<const Model>().kind(flecs::OnUpdate).each(render);
  world.system<const Camera>().kind(flecs::PreUpdate).each(pre_render);
  world.system().kind(flecs::PostUpdate).iter(post_render);

  world.set<Camera>({
    .position = {0.0f, 5.0f, -5.0f},
    .target = {0.0f, 0.0f, 0.0f},
    .up = {0.0f, 1.0f, 0.0f},
    .fovy = 45.0f,
    .projection = CAMERA_PERSPECTIVE,
  });

  world.observer<Model, const mesa::Transform>()
    .term_at(2)
    .event(flecs::OnSet)
    .each(update_model);

  world.observer<Model>().event(flecs::OnRemove).each(remove_model);

  world.entity<Player>()
    .set<Player>({})
    .set<Position>({0.0f, 0.0f, 0.0f})
    .set<Rotation>({0.0f, 0.0f, 0.0f})
    .set<Model>(LoadModelFromMesh(GenMeshCube(1.0f, 2.0f, 1.0f)));

  world.system<Position>().term<Position>().src<Player>().each(
    [](flecs::entity e, Position& pos) {
      e.set<Position>(Position(Vector3AddValue(pos, 0.5)));
    }
  );

  while (world.progress(GetFrameTime()) && !WindowShouldClose()) {
  }

  CloseWindow();
}
