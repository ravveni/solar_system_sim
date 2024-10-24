// celestial_body.h

#ifndef celestial_body_h
#define celestial_body_h

#include "raylib.h"
#include "raymath.h"

typedef struct {
    int id;
    float mass;
    float radius;
    Color color;
    Vector2 position;
    Vector2 velocity;
} CelestialBody;

CelestialBody create_celestial_body(int id, float radius, Color color, float surface_gravity, Vector2 initial_position, Vector2 initial_velocity);
void draw_celestial_body(CelestialBody *celestial_body);
void update_velocity(CelestialBody allBodies[], CelestialBody *currentBody, int total);

#endif
