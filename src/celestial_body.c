// celestial_body.c
#include "celestial_body.h"
#include "stdio.h"

#define GRAVITATIONAL_CONSTANT 0.0001f

CelestialBody CreateCelestialBody(int id, float radius, Color color, float surfaceGravity, Vector2 initialPosition, Vector2 initialVelocity) {
    CelestialBody celestial_body;
    celestial_body.id = id;
    celestial_body.mass = surfaceGravity * radius * radius / GRAVITATIONAL_CONSTANT;
    celestial_body.radius = radius;
    celestial_body.color = color;
    celestial_body.position = initialPosition;
    celestial_body.velocity = initialVelocity;
    return celestial_body;
}

void DrawCelestialBody(CelestialBody *celestialBody) {
    DrawCircle(celestialBody->position.x, celestialBody->position.y, celestialBody->radius, celestialBody->color);
}

Vector2 Vector2DivideValue(Vector2 vector, float value) {
    Vector2 vectoredValue = {value, value};
    return Vector2Divide(vector, vectoredValue);
}

Vector2 Vector2MultiplyValue(Vector2 vector, float value) {
    Vector2 vectoredValue = {value, value};
    return Vector2Multiply(vector, vectoredValue);
}

void UpdateVelocity(CelestialBody allBodies[], CelestialBody *currentBody, int total) {
    for (int i = 0; i < total; i++) {
        if (allBodies[i].id != currentBody->id) {
            float dstSqr = Vector2DistanceSqr(allBodies[i].position, currentBody->position);
            Vector2 forceDir = Vector2Normalize(Vector2Subtract(allBodies[i].position, currentBody->position));
            Vector2 acceleration = Vector2DivideValue(Vector2MultiplyValue(Vector2MultiplyValue(forceDir, GRAVITATIONAL_CONSTANT), allBodies[i].mass), dstSqr);

            currentBody->velocity = Vector2Add(currentBody->velocity, acceleration);
            currentBody->position = Vector2Add(currentBody->velocity, currentBody->position);
        }
    }
}
