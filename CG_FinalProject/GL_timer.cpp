﻿// 타이머
#include "config.h"
#include "gl_func.h"
#include "cannon.h"
#include "Razer.h"
#include "RazerLauncher.h"
#include <iostream>
#include <random>

extern bool key_w;
extern bool key_a;
extern bool key_s;
extern bool key_d;
extern bool key_j;

extern float go_lr;
extern float go_fb;
extern float robot_arm_angle;
extern float go_jump;

float jump_max = 1.2;//
bool robot_joint_dir = true;
bool jump_up_down = true;
float robot_speed = 0.05;//
int robot_joint_speed = 3;

void timerOperation(int value) {
	//랜덤 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 4); // 0부터 12까지의 범위에서 랜덤한 수 생성

	static int makecannonball_count = 1;//포탄 생산 카운트
	//포탄 이동
	for (int i = 0; i < MODEL_COUNT; i++) {
		if (objects[i].NewObject == 'c' || objects[i].NewObject == 'b')
			objects[i].tz += 0.1;
		if(objects[i].tz >= 10)
			objects[i].NewObject = '0';
	}
	for (int i = 0; i < MODEL_COUNT; i++) {
		if (objects[i].NewObject == 'r' || objects[i].NewObject == 'R') {
			objects[i].lifetime += 1;
			if (objects[i].NewObject == 'r') {
				objects[i].r = 0.5;
				objects[i].g = 0.2;
				objects[i].b = 0.2;

			}
			if (objects[i].lifetime > 100) {
				//objects[i].ry += 1;
				if (objects[i].NewObject == 'r') {
					objects[i].r = 1.0;
					objects[i].g = 0.0;
					objects[i].b = 0.0;
				}
			}
			if (objects[i].lifetime > 200) {
				objects[i].NewObject = '0';
			}
		}
	}

	//포탄 생산
	if (makecannonball_count % 100 == 0) {
		int randomAngle = dis(gen) * 30; //30배수로 랜덤 각도 생성
		make_cannonball(-10, 0.05, randomAngle);
	}
	else if (makecannonball_count % 70 == 0) {
		int randomAngle = dis(gen) * 90;
		make_razer(0, 1, randomAngle);
		make_razerLauncher(-10, 1, randomAngle);

	}
	makecannonball_count++;

	//이동
	{
		if (key_w)
		{
			go_fb -= robot_speed;
		}
		if (key_a)
		{
			go_lr -= robot_speed;
		}
		if (key_s)
		{
			go_fb += robot_speed;
		}
		if (key_d)
		{
			go_lr += robot_speed;
		}
		if (key_w || key_a || key_s || key_d)
		{
			if (robot_joint_dir)
			{
				robot_arm_angle += robot_joint_speed;
				if (robot_arm_angle > 45)
				{
					robot_joint_dir = false;
				}
			}
			else
			{
				robot_arm_angle -= robot_joint_speed;
				if (robot_arm_angle < -45)
				{
					robot_joint_dir = true;
				}
			}
		}
		if (key_j)
		{
			if (jump_up_down)
			{
				go_jump += 0.04;
				if (go_jump > jump_max)
				{
					jump_up_down = false;
				}
			}
			else
			{
				go_jump -= 0.04;
				if (go_jump < 0)
				{
					go_jump += 0.04;
					jump_up_down = true;
					key_j = false;
				}
			}
		}
	}

	glutTimerFunc(TIMER_SPEED, timerOperation, 1);
	glutPostRedisplay();
}
