#include "config.h"

OBJECTS objects[300] = {};
int object_num = 100;

glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos;
glm::mat4 transformMatrix, view, projection, lightMatrix;

unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
unsigned int lightPosLocation, lightColorLocation, objColorLocation;