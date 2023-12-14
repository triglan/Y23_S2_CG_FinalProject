// 키보드 조작
#include "gl_func.h"
#include "cannon.h"
bool key_w = false;
bool key_a = false;
bool key_s = false;
bool key_d = false;
bool key_j = false;
extern float robot_arm_angle;
extern float robot_screw_angle;

void keyDown(unsigned char KEY, int x, int y) {
	switch (KEY) {
	case 27:  // ESC
		glutDestroyWindow(1);
		break;
	case 'w':
		key_w = true;
		robot_screw_angle = 180;
		break;
	case 'a':
		key_a = true;
		robot_screw_angle = -90;
		break;
	case 's':
		key_s = true;
		robot_screw_angle = 0;
		break;
	case 'd':
		key_d = true;
		robot_screw_angle = 90;
		break;
	case 'j':
		key_j = true;
		break;
	case 'r':
		resume_game = true;
		game_clear = false;
		SunAngle = -85.f;
		for (int i = 0; i < MODEL_COUNT; i++)
		{
			objects[i].NewObject = '0';
		}
		for (int i = 0; i < 12; i++)
		{
			make_cannon(-9, 1, 15 + i * 30);
		}
		lightColor[0] = 1.0f, lightColor[1] = 1.0f, lightColor[2] = 1.0f;
	}
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}

void keyUp(unsigned char KEY, int x, int y) {
	switch (KEY) {
	case 0:
		break;
	case 'w':
		key_w = false;
		robot_arm_angle = 0;
		break;
	case 'a':
		key_a = false;
		robot_arm_angle = 0;
		break;
	case 's':
		key_s = false;
		robot_arm_angle = 0;
		break;
	case 'd':
		key_d = false;
		robot_arm_angle = 0;
		break;
	}
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}
