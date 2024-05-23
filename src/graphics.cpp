#include "graphics.hpp"
#include "transform.hpp"
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>

namespace mesa {

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

static void update_model(Model& m, const Transform& t) {
  m.transform = t;
}

static void remove_model(Model& m) {
  UnloadModel(m);
}

static void remove_shared_mesh_model(Model& m) {
}

graphics::graphics(flecs::world& world) {
  // Rendering pipeline
  world.system<const Model>().kind(flecs::OnUpdate).each(render);
  world.system<const Camera>().kind(flecs::PreUpdate).each(pre_render);
  world.system().kind(flecs::PostUpdate).iter(post_render);

  // Update model transforms
  world.observer<Model, const Transform>()
    .term_at(2)
    .event(flecs::OnSet)
    .each(update_model);

  // Ensure models are properly disposed on remove
  world.observer<Model>()
    .event(flecs::OnRemove)
    .without<SharedMesh>()
    .each(remove_model);
}

}
