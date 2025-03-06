#include "Portal.h"
#include "Wall.h"
#include "raylib.h"
#include <vector>
#include <iostream>
#include <cmath>

constexpr int screenWidth = 600;
constexpr int screenHeight = 600;
constexpr int FPS = 60;
const char *winTitle = "Raylib Practice";

bool currentPortal = true;
Portal *portals[2] = {nullptr, nullptr};
std::vector<Wall> walls;
int portalsIndex = 0;

constexpr Vector2 plrRectSize = {50.0f, 50.0f};
constexpr Vector2 origin = { 25.0f, 25.0f };
float angle = 90.0f;
Rectangle plrRect = {screenWidth / 2 - plrRectSize.y / 2, screenHeight /2 - plrRectSize.y / 2, plrRectSize.x, plrRectSize.y};
Vector2 posToPlacePortal;

bool collision = false;

void drawWindow();
void checkForPlayerCollision();

int main() {
  InitWindow(screenWidth, screenHeight, winTitle);

  SetTargetFPS(FPS);

  float dt;

  while (!WindowShouldClose()) {
    dt = GetFrameTime();

    // ---------------------------
    // movement
    if (IsKeyDown(KEY_A)) {
      angle -= 3 * dt * 100;
    }

    if (IsKeyDown(KEY_D)) {
      angle += 3 * dt * 100;
    }

    if (IsKeyDown(KEY_W)) {
      plrRect.x -= (3 * dt * 100) * (cos(angle * (PI / 180)));
      plrRect.y -= (3 * dt * 100) * (sin(angle * (PI / 180)));
    }

    if (IsKeyDown(KEY_S)) {
      plrRect.x -= -1 * (3 * dt * 100) * (cos(angle * (PI / 180)));
      plrRect.y -= -1 * (3 * dt * 100) * (sin(angle * (PI / 180)));
    }

    // ---------------------------

    // ---------------------------
    // make sure the player doesn't go off-screen
    if (plrRect.x < 0) {
      plrRect.x = 0;
    }

    if (plrRect.x + plrRectSize.x > screenWidth) {
      plrRect.x = screenWidth - plrRectSize.x;
    }

    if (plrRect.y < 0) {
      plrRect.y = 0;
    }

    if (plrRect.y + plrRectSize.y > screenHeight) {
      plrRect.y = screenHeight - plrRectSize.y;
    }
    // ---------------------------

    // ---------------------------
    // portal & wall placement and remove

    if (portals[0] == nullptr) {
      portalsIndex = 0;
    } else if (portals[1] == nullptr) {
      portalsIndex = 1;
    }

    posToPlacePortal = { plrRect.x + plrRectSize.x / 2 - 15,
                        plrRect.y + plrRectSize.y / 2 - 15};

    std::cout << plrRect.y << '\n';

    if (IsKeyPressed(KEY_Q)) {

      if (portals[0] == nullptr) {
        portals[0] = new Portal(posToPlacePortal, BLUE, portals[1]);
      } else {
        portals[0]->setPos(posToPlacePortal);
      }

    } else if (IsKeyPressed(KEY_E)) {
      if (portals[1] == nullptr) {
        portals[1] = new Portal(posToPlacePortal, ORANGE, portals[0]);
      } else {
        portals[1]->setPos(posToPlacePortal);
      }
    }

    if (IsKeyPressed(KEY_R)) {
      if (portals[1] != nullptr) {
        portals[1]->unBind();
        delete portals[1];
        portals[1] = nullptr;
      } else if (portals[0] != nullptr) {
        portals[0]->unBind();
        delete portals[0];
        portals[0] = nullptr;
      }
    }

    if (IsKeyPressed(KEY_F)) {
    }
    // ---------------------------

    checkForPlayerCollision();

    // ---------------------------
    // drawing

    drawWindow();

    // ---------------------------
  }

  delete portals[0];
  portals[0] = nullptr;

  delete portals[1];
  portals[1] = nullptr;
}

void drawWindow() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawRectanglePro(plrRect, origin, angle, BLACK);

  for (int i = 0; i < 2; ++i) {
    if (portals[i] != nullptr) {
      portals[i]->draw();
    }
  }

  EndDrawing();
}

void checkForPlayerCollision() {
  Vector2 pos = { plrRect.x, plrRect.y };

  if (portals[0] != nullptr) {
    collision = (CheckCollisionRecs(plrRect, portals[0]->getRectangle()) && portals[0]->isActivated());


    if (collision) {
      portals[0]->teleportToCounterpart(pos, plrRectSize);
    }
  }

  if (portals[1] != nullptr) {
    collision = (CheckCollisionRecs(plrRect, portals[1]->getRectangle()) && portals[1]->isActivated());

    if (collision) {
      portals[1]->teleportToCounterpart(pos, plrRectSize);
    }
  }

  plrRect.x = pos.x;
  plrRect.y = pos.y;
}
