#include "celestial_body.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define SCREEN_CENTER (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}

#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define SUN_COLOR ORANGE
#define SUN_RADIUS 200.0f

#define PLANET_COLOR DARKBLUE
#define PLANET_RADIUS 50.0f

#define MOON_COLOR LIGHTGRAY
#define MOON_RADIUS 5.0f

typedef enum {
    SUN,
    PLANET,
    MOON,
    COUNT
} CelestialBodies;

CelestialBody allBodies[COUNT];

void init() {
    allBodies[SUN] = CreateCelestialBody(SUN, SUN_RADIUS, SUN_COLOR, 10, SCREEN_CENTER, (Vector2){0, 0});
    Vector2 initialPlanetPosition = {allBodies[SUN].position.x + 2000.0f, allBodies[SUN].position.y};
    allBodies[PLANET] = CreateCelestialBody(PLANET, PLANET_RADIUS, PLANET_COLOR, 4, initialPlanetPosition, (Vector2){0, 10});
    Vector2 initialMoonPosition = {allBodies[PLANET].position.x + 150.0f, allBodies[PLANET].position.y};
    allBodies[MOON] = CreateCelestialBody(MOON, MOON_RADIUS, MOON_COLOR, 2, initialMoonPosition, (Vector2){0, 4});
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System Simulation");
    SetTargetFPS(60);

    init();

    Camera2D camera = {0};
    camera.zoom = 0.20f;
    camera.offset = SCREEN_CENTER;

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(NEARBLACK);
        for (int i = 0; i < COUNT; i++) {
            UpdateVelocity(allBodies, &allBodies[i], COUNT);
            camera.target = allBodies[SUN].position;

            DrawCelestialBody(&allBodies[i]);
        }
        EndMode2D();
        EndDrawing();
    }

    return 0;
}
