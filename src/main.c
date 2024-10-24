#include "celestial_body.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define SCREEN_CENTER (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}

#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define SUN_COLOR ORANGE
#define SUN_RADIUS 200.0f

#define INFERNO_COLOR MAROON
#define INFERNO_RADIUS 7.5f

#define BLUEDOT_COLOR DARKBLUE
#define BLUEDOT_RADIUS 50.0f

#define MOON_COLOR LIGHTGRAY
#define MOON_RADIUS 5.0f

typedef enum {
    SUN,
    INFERNO,
    BLUEDOT,
    MOON,
    COUNT
} CelestialBodies;

CelestialBody* allBodies[COUNT];

void init() {
    allBodies[SUN] = CreateCelestialBody(SUN, SUN_RADIUS, SUN_COLOR, 20, SCREEN_CENTER, (Vector2){0, 0});
    Vector2 initialInfernoPosition = {allBodies[SUN]->position.x + 500.0f, allBodies[SUN]->position.y};
    allBodies[INFERNO] = CreateCelestialBody(INFERNO, INFERNO_RADIUS, INFERNO_COLOR, 2, initialInfernoPosition, (Vector2){0, 25});
    Vector2 initialBluedotPosition = {allBodies[SUN]->position.x + 3000.0f, allBodies[SUN]->position.y};
    allBodies[BLUEDOT] = CreateCelestialBody(BLUEDOT, BLUEDOT_RADIUS, BLUEDOT_COLOR, 10, initialBluedotPosition, (Vector2){0, 9});
    Vector2 initialMoonPosition = {allBodies[BLUEDOT]->position.x + 125.0f, allBodies[BLUEDOT]->position.y};
    allBodies[MOON] = CreateCelestialBody(MOON, MOON_RADIUS, MOON_COLOR, 1, initialMoonPosition, (Vector2){0, 1});
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System Simulation");
    SetTargetFPS(60);

    init();

    Camera2D camera = {0};
    camera.zoom = 0.15f;
    camera.offset = SCREEN_CENTER;

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(NEARBLACK);
        for (int i = 0; i < COUNT; i++) {
            UpdateCelestialBody(allBodies, allBodies[i], COUNT);
            camera.target = allBodies[SUN]->position;

            DrawCelestialBody(allBodies[i]);
            DrawPositionHistory(allBodies[i]);
        }
        EndMode2D();
        EndDrawing();
    }

    return 0;
}
