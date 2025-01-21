// celestial_body.c

#include "celestial_body.h"

#define GRAVITATIONAL_CONSTANT 0.0001f
#define HISTORIC_POSITION_RADIUS 5.0f

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

void DestroyCelestialBody(CelestialBody *celestialBody) {
    free(celestialBody);
}

void DrawCelestialBody(CelestialBody *celestialBody) {
    DrawCircleV(celestialBody->position, celestialBody->radius, celestialBody->color);
}

void DrawHistoricPositions(CelestialBody *celestialBody) {
    for (int i = 0; i < MAX_POSITIONS; i++) {
        DrawCircleV(celestialBody->historicPositions[i], HISTORIC_POSITION_RADIUS, celestialBody->color);
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

void UpdateCelestialBody(CelestialBody *solarSystem[], int celestialBodiesCount, int currentIndex) {
    for (int i = 0; i < celestialBodiesCount; i++) {
        if (solarSystem[i]->id != solarSystem[currentIndex]->id) {
            float dstSqr = Vector2DistanceSqr(solarSystem[i]->position, solarSystem[currentIndex]->position );
            Vector2 forceDir = Vector2Normalize(Vector2Subtract(solarSystem[i]->position, solarSystem[currentIndex]->position));
            Vector2 acceleration = Vector2DivideValue(Vector2MultiplyValue(Vector2MultiplyValue(forceDir, GRAVITATIONAL_CONSTANT), solarSystem[i]->mass), dstSqr);

            solarSystem[currentIndex]->velocity = Vector2Add(solarSystem[currentIndex]->velocity, acceleration);
            solarSystem[currentIndex]->position = Vector2Add(solarSystem[currentIndex]->velocity, solarSystem[currentIndex]->position);

            solarSystem[currentIndex]->historicPositions[solarSystem[currentIndex]->historicPositionIndex] = solarSystem[currentIndex]->position;
            solarSystem[currentIndex]->historicPositionIndex = (solarSystem[currentIndex]->historicPositionIndex + 1) % MAX_POSITIONS;
        }
    }
}
