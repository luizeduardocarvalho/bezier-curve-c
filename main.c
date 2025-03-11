#include "include/raylib.h"

#define SPEED 0.2
#define STEP 0.001f
#define SIZE ((int)(1.0f / STEP) + 1)

typedef enum { FALSE = 0, TRUE = 1 } boolean;

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

Vector2 getBezierPoint(Vector2 a, Vector2 b, Vector2 c, double t) {
  Vector2 bezierPoint;
  bezierPoint.x =
      (1 - t) * ((1 - t) * a.x + t * b.x) + t * ((1 - t) * b.x + t * c.x);

  bezierPoint.y =
      (1 - t) * ((1 - t) * a.y + t * b.y) + t * ((1 - t) * b.y + t * c.y);

  return bezierPoint;
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  Vector2 circlePos[3] = {{screenWidth / 2 - 50, screenHeight / 2},
                          {screenWidth / 2, screenHeight / 2},
                          {screenWidth / 2 + 50, screenHeight / 2}};

  Vector2 circleTPos[2] = {{circlePos[0].x, circlePos[0].y},
                           {circlePos[1].x, circlePos[1].y}};

  Vector2 bezierCurve[SIZE] = {{0, 0}};

  int stepCount = 0;
  int circleRadius = 6;
  int draggingCircle = -1;

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

      circleTPos[0].x = circlePos[0].x + t * (circlePos[1].x - circlePos[0].x);
      circleTPos[0].y = circlePos[0].y + t * (circlePos[1].y - circlePos[0].y);
      circleTPos[1].x = circlePos[1].x + t * (circlePos[2].x - circlePos[1].x);
      circleTPos[1].y = circlePos[1].y + t * (circlePos[2].y - circlePos[1].y);

      Vector2 bezierPos =
          getBezierPoint(circlePos[0], circlePos[1], circlePos[2], t);

      if (stepCount < SIZE && t >= (stepCount * STEP)) {
        bezierCurve[stepCount++] =
            (Vector2){.x = bezierPos.x, .y = bezierPos.y};
      }
    }

    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      for (int i = 0; i < 3; i++) {
        if (isMouseOverlapping(mousePos, circlePos[i], circleRadius)) {
          draggingCircle = i;
          break;
        }
      }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      draggingCircle = -1;
    }

    if (draggingCircle != -1) {
      circlePos[draggingCircle] = mousePos;
    }

    if (IsKeyPressed(KEY_R)) {
      t = 0;
      circleTPos[0] = circlePos[0];
      circleTPos[1] = circlePos[1];
      stepCount = 0;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawLineEx(circlePos[0], circlePos[1], 3.0, RED);
    DrawLineEx(circlePos[1], circlePos[2], 3.0, RED);

    // Draw reference points
    for (int i = 0; i < 3; i++) {
      DrawCircle(circlePos[i].x, circlePos[i].y, circleRadius, BLACK);
    }

    DrawLineEx(circleTPos[0], circleTPos[1], 3.0, GREEN);

    DrawCircle(circleTPos[0].x, circleTPos[0].y, 3, GREEN);
    DrawCircle(circleTPos[1].x, circleTPos[1].y, 3, GREEN);

    for (int i = 1; i < SIZE; i++) {
      if (bezierCurve[i].x != 0 && bezierCurve[i].y != 0) {
        DrawLineEx(bezierCurve[i], bezierCurve[i - 1], 2.0, PURPLE);
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
