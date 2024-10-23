#include "celestial_body.h"
#include "stdio.h"

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
#define MOON_INITIAL_VELOCITY 1.5f

CelestialBody all_bodies[ENTITY_COUNT];

void init() {
    all_bodies[SUN] = create_celestial_body(SUN, SUN_RADIUS, SUN_COLOR, 10, SCREEN_CENTER, (Vector2){0, 0});
    Vector2 initial_planet_position = {all_bodies[SUN].position.x + 2000.0f, all_bodies[SUN].position.y};
    all_bodies[PLANET] = create_celestial_body(PLANET, PLANET_RADIUS, PLANET_COLOR, 4, initial_planet_position, (Vector2){0, 10});
    Vector2 initial_moon_position = {all_bodies[PLANET].position.x + 150.0f, all_bodies[PLANET].position.y};
    all_bodies[MOON] = create_celestial_body(MOON, MOON_RADIUS, MOON_COLOR, 2, initial_moon_position, (Vector2){0, 4});
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
        for (int i = 0; i < ENTITY_COUNT; i++) {
            update_velocity(all_bodies, &all_bodies[i]);
            camera.target = all_bodies[SUN].position;

            draw_celestial_body(&all_bodies[i]);
        }
        EndMode2D();
        EndDrawing();
    }

    return 0;
}
