#include "config.h"

OBJECTS objects[MODEL_COUNT] = {};
int object_num = 0;
int cannonball_num = 1000;

glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos;
glm::mat4 transformMatrix, view, projection, lightMatrix;

unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
unsigned int lightPosLocation, lightColorLocation, objColorLocation;

int TIMER_SPEED = 17;