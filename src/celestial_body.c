// celestial_body.c

#include "celestial_body.h"

#define GRAVITATIONAL_CONSTANT 0.0001f

CelestialBody* CreateCelestialBody(int id, float radius, Color color, float surfaceGravity, Vector2 initialPosition, Vector2 initialVelocity) {
    CelestialBody *celestialBody = malloc(sizeof(CelestialBody));

    if (!celestialBody) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    celestialBody->id = id;
    celestialBody->mass = surfaceGravity * radius * radius / GRAVITATIONAL_CONSTANT;
    celestialBody->radius = radius;
    celestialBody->color = color;
    celestialBody->position = initialPosition;
    celestialBody->velocity = initialVelocity;
    celestialBody->historicPositionIndex = 0;

    for (int i = 0; i < MAX_POSITIONS; i++) {
        celestialBody->historicPositions[i] = Vector2Zero();
    }

    return celestialBody;
}

void DrawCelestialBody(CelestialBody *celestialBody) {
    DrawCircle(celestialBody->position.x, celestialBody->position.y, celestialBody->radius, celestialBody->color);
}

void DrawPositionHistory(CelestialBody *celestialBody) {
    for (int i = 0; i < MAX_POSITIONS; i++) {
        DrawCircleV(celestialBody->historicPositions[i], 5.0f, celestialBody->color);
    }
}

Vector2 Vector2DivideValue(Vector2 vector, float value) {
    Vector2 vectoredValue = {value, value};
    return Vector2Divide(vector, vectoredValue);
}

Vector2 Vector2MultiplyValue(Vector2 vector, float value) {
    Vector2 vectoredValue = {value, value};
    return Vector2Multiply(vector, vectoredValue);
}

void UpdateCelestialBody(CelestialBody *allBodies[], CelestialBody *currentBody, int total) {
    for (int i = 0; i < total; i++) {
        if (allBodies[i]->id != currentBody->id) {
            float dstSqr = Vector2DistanceSqr(
                allBodies[i]->position,
                currentBody->position
            );
            Vector2 forceDir = Vector2Normalize(
                Vector2Subtract(
                    allBodies[i]->position,
                    currentBody->position
                )
            );
            Vector2 acceleration = Vector2DivideValue(
                Vector2MultiplyValue(
                    Vector2MultiplyValue(
                        forceDir,
                        GRAVITATIONAL_CONSTANT
                    ),
                    allBodies[i]->mass
                ),
                dstSqr
            );

            currentBody->velocity = Vector2Add(currentBody->velocity, acceleration);
            currentBody->position = Vector2Add(currentBody->velocity, currentBody->position);

            currentBody->historicPositions[currentBody->historicPositionIndex] = currentBody->position;
            currentBody->historicPositionIndex = (currentBody->historicPositionIndex + 1) % 100;
        }
    }
}
