// celestial_body.h

#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_POSITIONS 100

typedef struct {
    int id;
    float mass;
    float radius;
    Color color;
    Vector2 position;
    Vector2 velocity;
    int historicPositionIndex;
    Vector2 historicPositions[MAX_POSITIONS];
} CelestialBody;

CelestialBody* CreateCelestialBody(int id, float radius, Color color, float surfaceGravity, Vector2 initialPosition, Vector2 initialVelocity);

void DestroyCelestialBody(CelestialBody *celestialBody);

void DrawCelestialBody(CelestialBody *celestialBody);

void DrawHistoricPositions(CelestialBody *celestialBody);

void UpdateCelestialBody(CelestialBody *solarSystem[], int celestialBodiesCount, int currentIndex);

#endif
