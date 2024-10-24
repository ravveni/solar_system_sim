// celestial_body.c
#include "celestial_body.h"

#define GRAVITATIONAL_CONSTANT 0.0001f

CelestialBody create_celestial_body(int id, float radius, Color color, float surface_gravity, Vector2 initial_position, Vector2 initial_velocity) {
    CelestialBody celestial_body;
    celestial_body.id = id;
    celestial_body.mass = surface_gravity * radius * radius / GRAVITATIONAL_CONSTANT;
    celestial_body.radius = radius;
    celestial_body.color = color;
    celestial_body.position = initial_position;
    celestial_body.velocity = initial_velocity;
    return celestial_body;
}

void draw_celestial_body(CelestialBody *celestial_body) {
    DrawCircle(celestial_body->position.x, celestial_body->position.y, celestial_body->radius, celestial_body->color);
}

Vector2 Vector2DivideValue(Vector2 vector, float value) {
    Vector2 vectored_value = {value, value};
    return Vector2Divide(vector, vectored_value);
}

Vector2 Vector2MultiplyValue(Vector2 vector, float value) {
    Vector2 vectored_value = {value, value};
    return Vector2Multiply(vector, vectored_value);
}

void update_velocity(CelestialBody all_bodies[], CelestialBody *current_body) {
    for (int i = 0; i < 3; i++) {
        if (all_bodies[i].id != current_body->id) {
            float sqr_dst = Vector2DistanceSqr(all_bodies[i].position, current_body->position);
            Vector2 force_dir = Vector2Normalize(Vector2Subtract(all_bodies[i].position, current_body->position));
            Vector2 acceleration = Vector2DivideValue(Vector2MultiplyValue(Vector2MultiplyValue(force_dir, GRAVITATIONAL_CONSTANT), all_bodies[i].mass), sqr_dst);

            current_body->velocity = Vector2Add(current_body->velocity, acceleration);
            current_body->position = Vector2Add(current_body->velocity, current_body->position);
        }
    }
}
