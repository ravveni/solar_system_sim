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

CelestialBody all_bodies[3];

void init() {
    all_bodies[0] = create_celestial_body(0, SUN_RADIUS, SUN_COLOR, 10, SCREEN_CENTER, (Vector2){0, 0});
    Vector2 initial_planet_position = {all_bodies[0].position.x + 2000.0f, all_bodies[0].position.y};
    all_bodies[1] = create_celestial_body(1, PLANET_RADIUS, PLANET_COLOR, 4, initial_planet_position, (Vector2){0, 10});
    Vector2 initial_moon_position = {all_bodies[1].position.x + 150.0f, all_bodies[1].position.y};
    all_bodies[2] = create_celestial_body(2, MOON_RADIUS, MOON_COLOR, 2, initial_moon_position, (Vector2){0, 4});
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
        for (int i = 0; i < 3; i++) {
            update_velocity(all_bodies, &all_bodies[i]);
            camera.target = all_bodies[0].position;

            draw_celestial_body(&all_bodies[i]);
        }
        EndMode2D();
        EndDrawing();
    }

    return 0;
}
