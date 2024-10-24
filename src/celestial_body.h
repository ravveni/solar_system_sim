// celestial_body.h

#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

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

CelestialBody CreateCelestialBody(int id, float radius, Color color, float surfaceGravity, Vector2 initialPosition, Vector2 initialVelocity);
void DrawCelestialBody(CelestialBody *celestialBody);
void UpdateVelocity(CelestialBody allBodies[], CelestialBody *currentBody, int total);

#endif
