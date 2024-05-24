#include "animation.hpp"
#include "camera.hpp"
#include "config.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "physics.hpp"
#include "player.hpp"
#include "transform.hpp"
#include <flecs.h>
#include <raylib.h>
#include <rlgl.h>

int main() {
  InitWindow(mesa::WINDOW_WIDTH, mesa::WINDOW_HEIGHT, mesa::WINDOW_TITLE);
  SetTargetFPS(60);
  DisableCursor();

  flecs::world world;

  world.import <mesa::transform>();
  world.import <mesa::graphics>();
  world.import <mesa::animation>();
  world.import <mesa::camera>();
  world.import <mesa::physics>();
  world.import <mesa::input>();
  world.import <mesa::player>();

  // Load a bunch of random models for testing

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
