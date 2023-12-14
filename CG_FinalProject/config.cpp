#include "config.h"

OBJECTS objects[MODEL_COUNT] = {};
int object_num = 100;
int cannonball_num = 1000;

glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos;
glm::mat4 transformMatrix, view, projection, lightMatrix;
glm::mat4 transformMatrix2;//


unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
unsigned int lightPosLocation, lightColorLocation, objColorLocation;

GLfloat lightColor[3] = {1.0, 1.0, 1.0};

bool resume_game = true;
bool game_clear = false;
int TIMER_SPEED = 17;

GLfloat SunAngle = -85.0f;

//FMOD::System* ssystem;
//FMOD::Sound* sound1, * sound2;
//FMOD::Channel* channel = 0;
//FMOD_RESULT result;
//void* extradriverdata = 0;