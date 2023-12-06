#include "config.h"

OBJECTS objects[MODEL_COUNT] = {};
int object_num = 100;
int cannonball_num = 1000;

glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos;
glm::mat4 transformMatrix, view, projection, lightMatrix;
glm::mat4 transformMatrix2;//


unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
unsigned int lightPosLocation, lightColorLocation, objColorLocation;

int TIMER_SPEED = 17;

GLfloat SunAngle = -85.0f;