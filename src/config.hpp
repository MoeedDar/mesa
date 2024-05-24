#pragma once

namespace mesa {

static constexpr const int WINDOW_WIDTH = 1280;
static constexpr const int WINDOW_HEIGHT = 780;
static constexpr const char* WINDOW_TITLE = "Mesa";
static constexpr const float MOUSE_SENSITIVITY = 0.2f;
static constexpr const float PLAYER_VELOCITY = 20.0f;
static constexpr const float PLAYER_HEIGHT = 2.0f;
static constexpr const float RELATIVE_CAMERA_HEIGHT = 0.8f;
static constexpr const float CAMERA_HEIGHT =
  PLAYER_HEIGHT * RELATIVE_CAMERA_HEIGHT;
static constexpr const float RELATIVE_CAMERA_FORWARD = 0.19;

}
