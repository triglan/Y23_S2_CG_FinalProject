// 타이머
#include "config.h"
#include "gl_func.h"
#include "cannon.h"
#include "Razer.h"
#include <iostream>
#include <random>

void timerOperation(int value) {
	//랜덤 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 12); // 0부터 12까지의 범위에서 랜덤한 수 생성

	static int makecannonball_count = 1;//포탄 생산 카운트
	//포탄 이동
	for (int i = 0; i < MODEL_COUNT; i++) {
		if (objects[i].NewObject == 'c')
			objects[i].tz += 0.1;
		if(objects[i].tz >= 10)
			objects[i].NewObject = '0';
	}
	for (int i = 0; i < MODEL_COUNT; i++) {
		if (objects[i].NewObject == 'r') {
			objects[i].lifetime += 1;
			objects[i].ry += 1;
			if (objects[i].lifetime > 100)
				objects[i].NewObject = '0';
		}
	}

	//포탄 생산
	if (makecannonball_count % 100 == 0) {
		int randomAngle = dis(gen) * 30; //30배수로 랜덤 각도 생성
		make_cannonball(-10, 0.05, randomAngle);
	}
	else if (makecannonball_count % 70 == 0) {
		int randomAngle = dis(gen) * 30;
		make_razer(0, 1, randomAngle);
	}
	makecannonball_count++;

	glutTimerFunc(TIMER_SPEED, timerOperation, 1);
	glutPostRedisplay();
}
