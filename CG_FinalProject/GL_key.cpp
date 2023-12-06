// 키보드 조작
#include "gl_func.h"
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
