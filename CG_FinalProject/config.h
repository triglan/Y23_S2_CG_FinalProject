// 전역 변수, 변수 열거형, 모델 출력 개수는 이곳에 선언 
// 프로젝트의 중요 헤더 파일들은 이 파일이 담당 
// 나머지 헤더 파일들은 이 파일에 대해 의존성을 가지고 있기 때문에 이 파일을 절대 삭제해서는 안됨.
#ifndef CONFIG_H
#define CONFIG_H
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4305)
#pragma warning(disable: 4326)
#pragma warning(disable: 4244)
#include <gl/glm/glm.hpp> //  이 include들을 다른데로 옮기지 말 것!
#include <gl/glm/ext.hpp> 
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#define WIDTH 800  
#define HEIGHT 800
#define X_POS 450
#define Y_POS 50

#define MODEL_COUNT 3000 // 모델 개수의 최대값
using namespace std;

//구조체 선언
typedef struct _OBJECTS {//translate 이동 xyz , scale 크기 xyz , rotate 회전 xyz 오브젝트 탬플릿
	char NewObject = '0';// 미리 생성된 오브젝트면 이를 통과함. 게임중 생성된 오브젝트라면 true로 바꾸고 아래를 사용함.
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;
	GLfloat r = 0.5, g = 0.5, b = 0.5;
	int lifetime = 0;
	bool life = true;
}OBJECTS;

//전역 변수 선언
extern int object_num;
extern int cannonball_num;
extern OBJECTS objects[MODEL_COUNT];//cpp에 선언하고 h에서 전방선언하기

extern glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos;
extern glm::mat4 transformMatrix, view, projection, lightMatrix;

extern unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
extern unsigned int lightPosLocation, lightColorLocation, objColorLocation;
extern GLfloat lightColor[3];

extern bool resume_game;
extern bool game_clear;

extern glm::mat4 transformMatrix2;//

extern int TIMER_SPEED;


enum bufferMode {  // 버퍼 모드. 버퍼 초기화 시 modeInit 사용, 버텍스 업데이트 시 modeUpdate 사용 
	modeInit, modeUpdate
};
enum projectionMode {  // 원근 투영 / 직각 투영. 기본 원근 투영 
	modeOrtho, modePers
};

extern GLfloat SunAngle;

#endif
