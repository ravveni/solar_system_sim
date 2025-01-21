#include "celestial_body.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define SCREEN_CENTER (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}

#define CAMERA_ZOOM 0.15f
#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define SUN_COLOR ORANGE
#define SUN_INITIAL_VELOCITY (Vector2){2, 2}
#define SUN_RADIUS 200.0f
#define SUN_SURFACE_GRAVITY 20

#define INFERNO_COLOR MAROON
#define INFERNO_INITIAL_DISTANCE 500.0f
#define INFERNO_INITIAL_VELOCITY (Vector2){2, 27}
#define INFERNO_RADIUS 7.5f
#define INFERNO_SURFACE_GRAVITY 2

#define BLUEDOT_COLOR DARKBLUE
#define BLUEDOT_INITIAL_DISTANCE 3000.0f
#define BLUEDOT_INITIAL_VELOCITY (Vector2){2, 11}
#define BLUEDOT_RADIUS 50.0f
#define BLUEDOT_SURFACE_GRAVITY 10

#define MOON_COLOR LIGHTGRAY
#define MOON_INITIAL_DISTANCE 125.0f
#define MOON_INITIAL_VELOCITY (Vector2){2, 3}
#define MOON_RADIUS 5.0f
#define MOON_SURFACE_GRAVITY 1

typedef enum {
    MOON,
    BLUEDOT,
    INFERNO,
    SUN,
    CELESTIAL_BODIES_COUNT
} CelestialBodyID;

Camera2D camera = {0};
CelestialBody* solarSystem[CELESTIAL_BODIES_COUNT];

void CreateSolarSystem() {
    solarSystem[SUN] = CreateCelestialBody(SUN, SUN_RADIUS, SUN_COLOR, SUN_SURFACE_GRAVITY, Vector2Zero(), SUN_INITIAL_VELOCITY);
    Vector2 initialInfernoPosition = {solarSystem[SUN]->position.x + INFERNO_INITIAL_DISTANCE, solarSystem[SUN]->position.y};
    solarSystem[INFERNO] = CreateCelestialBody(INFERNO, INFERNO_RADIUS, INFERNO_COLOR, INFERNO_SURFACE_GRAVITY, initialInfernoPosition, INFERNO_INITIAL_VELOCITY);
    Vector2 initialBluedotPosition = {solarSystem[SUN]->position.x + BLUEDOT_INITIAL_DISTANCE, solarSystem[SUN]->position.y};
    solarSystem[BLUEDOT] = CreateCelestialBody(BLUEDOT, BLUEDOT_RADIUS, BLUEDOT_COLOR, BLUEDOT_SURFACE_GRAVITY, initialBluedotPosition, BLUEDOT_INITIAL_VELOCITY);
    Vector2 initialMoonPosition = {solarSystem[BLUEDOT]->position.x + MOON_INITIAL_DISTANCE, solarSystem[BLUEDOT]->position.y};
    solarSystem[MOON] = CreateCelestialBody(MOON, MOON_RADIUS, MOON_COLOR, MOON_SURFACE_GRAVITY, initialMoonPosition, MOON_INITIAL_VELOCITY);
}

void SetupCamera() {
    camera.offset = SCREEN_CENTER;
    camera.zoom = CAMERA_ZOOM;
}

void Startup() {
    CreateSolarSystem();
    SetupCamera();
}

void Cleanup() {
    for (int i = 0; i < CELESTIAL_BODIES_COUNT; i++) {
        DestroyCelestialBody(solarSystem[i]);
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System Simulation");
    SetTargetFPS(60);
    Startup();

    while (!WindowShouldClose()) {
        ClearBackground(NEARBLACK);
        BeginDrawing();
        BeginMode2D(camera);

            camera.target = solarSystem[SUN]->position;

            for (int i = 0; i < CELESTIAL_BODIES_COUNT; i++) {
                UpdateCelestialBody(solarSystem, CELESTIAL_BODIES_COUNT, i);
                DrawCelestialBody(solarSystem[i]);
                DrawHistoricPositions(solarSystem[i]);
            }

        EndMode2D();
        EndDrawing();
    }

    Cleanup();
    return 0;
}
