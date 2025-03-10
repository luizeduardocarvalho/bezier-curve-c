#include "include/raylib.h"

typedef enum { FALSE = 0, TRUE = 1 } boolean;
const double SPEED = 0.2;
const double STEP = 0.01f;
const int SIZE = ((int)(1.0f / STEP) + 1);

boolean isMouseOverlapping(Vector2 mouse, Vector2 object,
                           int objectCenterDiff) {
  if (mouse.x >= object.x - objectCenterDiff &&
      mouse.x <= object.x + objectCenterDiff &&
      mouse.y >= object.y - objectCenterDiff &&
      mouse.y <= object.y + objectCenterDiff) {
    return TRUE;
  }

  return FALSE;
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  Vector2 circleAPos = {.x = screenWidth / 2 - 50, .y = screenHeight / 2};
  Vector2 circleBPos = {.x = screenWidth / 2, .y = screenHeight / 2};
  Vector2 circleCPos = {.x = screenWidth / 2 + 50, .y = screenHeight / 2};

  Vector2 circleTAPos = {.x = circleAPos.x, .y = circleAPos.y};
  Vector2 circleTBPos = {.x = circleBPos.x, .y = circleBPos.y};

  Vector2 bezierPos = {.x = circleAPos.x, .y = circleAPos.y};

  Vector2 bezierCurve[SIZE];
  /* for (int i = 0; i < SIZE - 1; i++) { */
  /*   bezierCurve[i] = circleAPos; */
  /* } */

  int stepCount = 0;

  int circleRadius = 6;

  int trackACircle = FALSE;
  int trackBCircle = FALSE;
  int trackCCircle = FALSE;

  double t = 0.0;

  InitWindow(screenWidth, screenHeight,
             "raylib [shapes] example - raylib logo using shapes");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    if (t < 1.0f) {
      if (t > 1.0f) {
        t = 1.0f;
      }

      t += SPEED * deltaTime;

      bezierPos.x = circleTAPos.x + t * (circleTBPos.x - circleTAPos.x);
      bezierPos.y = circleTAPos.y + t * (circleTBPos.y - circleTAPos.y);

      circleTAPos.x = circleAPos.x + t * (circleBPos.x - circleAPos.x);
      circleTAPos.y = circleAPos.y + t * (circleBPos.y - circleAPos.y);
      circleTBPos.x = circleBPos.x + t * (circleCPos.x - circleBPos.x);
      circleTBPos.y = circleBPos.y + t * (circleCPos.y - circleBPos.y);

      if (stepCount < SIZE && t >= (stepCount * STEP)) {
        bezierCurve[stepCount++] = bezierPos;
      }
    }

    if (trackACircle) {
      Vector2 mousePos = GetMousePosition();
      circleAPos.x = mousePos.x;
      circleAPos.y = mousePos.y;
    } else if (trackBCircle) {
      Vector2 mousePos = GetMousePosition();
      circleBPos.x = mousePos.x;
      circleBPos.y = mousePos.y;
    } else if (trackCCircle) {
      Vector2 mousePos = GetMousePosition();
      circleCPos.x = mousePos.x;
      circleCPos.y = mousePos.y;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Vector2 mousePos = GetMousePosition();
      if (isMouseOverlapping(mousePos, circleAPos, circleRadius)) {
        trackACircle = TRUE;
      } else if (isMouseOverlapping(mousePos, circleBPos, circleRadius)) {
        trackBCircle = TRUE;
      } else if (isMouseOverlapping(mousePos, circleCPos, circleRadius)) {
        trackCCircle = TRUE;
      }
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      trackACircle = FALSE;
      trackBCircle = FALSE;
      trackCCircle = FALSE;
    }

    if (IsKeyPressed(KEY_R)) {
      t = 0;
      circleTAPos.x = circleAPos.x;
      circleTAPos.y = circleAPos.y;
      circleTBPos.x = circleBPos.x;
      circleTBPos.y = circleBPos.y;

      stepCount = 0;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawLineEx(circleAPos, circleBPos, 3.0, RED);
    DrawLineEx(circleBPos, circleCPos, 3.0, RED);

    DrawCircle(circleAPos.x, circleAPos.y, circleRadius, BLACK);
    DrawCircle(circleBPos.x, circleBPos.y, circleRadius, BLACK);
    DrawCircle(circleCPos.x, circleCPos.y, circleRadius, BLACK);

    DrawLineEx(circleTAPos, circleTBPos, 3.0, GREEN);

    DrawCircle(circleTAPos.x, circleTAPos.y, 3, GREEN);
    DrawCircle(circleTBPos.x, circleTBPos.y, 3, GREEN);

    DrawCircle(bezierPos.x, bezierPos.y, 3, BLUE);

    for (int i = 0; i < SIZE - 1; i++) {
      DrawLineEx(bezierCurve[i], bezierCurve[i + 1], 2.0, PURPLE);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
