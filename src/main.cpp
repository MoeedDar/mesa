#include "camera.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "physics.hpp"
#include "player.hpp"
#include "transform.hpp"
#include <flecs.h>
#include <raylib.h>

static constexpr const int WINDOW_WIDTH = 800;
static constexpr const int WINDOW_HEIGHT = 600;
static constexpr const char* WINDOW_TITLE = "Mesa";

int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  DisableCursor();

  flecs::world world;

  world.import <mesa::transform>();
  world.import <mesa::graphics>();
  world.import <mesa::camera>();
  world.import <mesa::physics>();
  world.import <mesa::input>();
  world.import <mesa::player>();

  // world.entity().set<Model>(LoadModelFromMesh(GenMeshPlane(100, 100, 10,
  // 10)));

  Model models[100];
  for (auto& m : models) {
    Mesh mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    m = LoadModelFromMesh(mesh);
  }

  for (auto& m : models) {
    world.entity().set<mesa::Model>(m).set<mesa::Position>({
      static_cast<float>(rand() % 101 - 50),
      static_cast<float>(rand() % 101),
      static_cast<float>(rand() % 101 - 50),
    });
  }

  while (world.progress(GetFrameTime()) && !WindowShouldClose()) {
  }

  CloseWindow();
}
