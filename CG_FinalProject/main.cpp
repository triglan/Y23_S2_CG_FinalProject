#include "config.h"  // 중요 헤더 파일
#include "shader.h"  // 셰이더 생성
#include "buffer.h"  // 버퍼
#include "translate.h"  // 변환
#include "gl_func.h"  // GL 기능 함수
#include "cannon.h"
#include "RazerLauncher.h"
#include "Razer.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "soundController.cpp"

// fmod 객체 선언
// 채널, 사운드 파일 선언

FMOD::System* ssystem;
FMOD::Sound* bgm;
FMOD::Channel* bgmChannel = 0;
void* extradriverdata = 0;
FMOD_RESULT result;


void soundPlayer() {
	if (bgmStop) {
		bgmChannel->stop();
		bgmStop = false;
	}
	if (bgmPlay) {
		bgmChannel->stop();
		ssystem->playSound(bgm, 0, false, &bgmChannel);
		bgmPlay = false;
	}
}



extern GLuint ID;
int projectionMode = modePers;  // 직각투영/원근투영, 기본 원근투영 모드, modeOrtho로 변경 시 알아서 바뀜

GLvoid displayOutput() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glUseProgram(ID);
	

	setCamera(); // 이 부분은 여기서 건들 필요 없음
	setProjection(projectionMode); // 이 부분은 여기서 건들 필요 없음
	setLight();

	// MODEL_COUNT는 config.h에 정의되어있음
	for (int i = 0; i < MODEL_COUNT; i++) {  // MODEL_COUNT 만큼 반복문을 돌며 변환과 출력 반복
		setTransform(i);  // 변환 세팅
		finishTransform(i); // 변환을 glsl로 전달
		modelOutput(i);  // 최종 출력, 3개 함수 모두 modelOutput.cpp에 있음
	}
	soundPlayer();

	glutSwapBuffers();
}

GLvoid displayReshape(int w, int h) {
	glViewport(0, 0, w, h);
}
void main(int argc, char** argv) {
	{  // fold here
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GL_MULTISAMPLE);
		glutInitWindowPosition(X_POS, Y_POS);
		glutInitWindowSize(WIDTH, HEIGHT);
		glutCreateWindow("OpenGL");
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			cerr << "Unable to initialize GLEW" << endl;  exit(EXIT_FAILURE);
		}
		else cout << "GLEW Initialized" << endl;

		// fmod 초기화, 세팅
		// 브금의 경우 여기서 repeat play
		result = FMOD::System_Create(&ssystem); //--- 사운드 시스템 생성
		if (result != FMOD_OK)
			exit(0);
		ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata); //--- 사운드 시스템 초기화
		ssystem->createSound(".//Sounds//stage1.mp3", FMOD_LOOP_NORMAL, 0, &bgm); //--- 1번 사운드 생성 및 설정
		ssystem->playSound(bgm, 0, false, &bgmChannel);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		//glEnable(GL_CULL_FACE);
		makeShaderProgram();
	}
	{//유저
		for (int i = 0; i < 12; i++)
		{
			make_cannon(-9, 1, 15 + i * 30);
		}
	}
	// MODEL_COUNT는 config.h에 정의되어있음
	for(int i = 0; i < MODEL_COUNT; i ++)  // MODEL_COUNT 만큼 버퍼 초기화
		setBuffer(i, modeInit);  // modelBuffer.cpp에 있음
	
	glutDisplayFunc(displayOutput);
	glutReshapeFunc(displayReshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp); 
	glutTimerFunc(TIMER_SPEED, timerOperation, 1);
	glutMainLoop();
}