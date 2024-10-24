// celestial_body.h

#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "common.h"

typedef struct {
    int id;
    float mass;
    float radius;
    Color color;
    int currentPositionIndex;
    Vector2 positionHistory[100];
    Vector2 velocity;
} CelestialBody;

CelestialBody CreateCelestialBody(int id, float radius, Color color, float surfaceGravity, Vector2 initialPosition, Vector2 initialVelocity);
void DrawCelestialBody(CelestialBody *celestialBody);
void UpdateCelestialBody(CelestialBody allBodies[], CelestialBody *currentBody, int total);

#endif
