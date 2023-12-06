#include "translate.h"
#include "config.h"
#include "objects.h"

void make_cannon(GLfloat tz, GLfloat size, GLfloat angle) {//�ҷ��� �� ���� ����
	if (object_num < 100000 - 3) {
		//���� ���� ����
		{//tz�� -������ �־�� �ڿ��� ������ ������ �ٶ󺸰� ����
			objects[object_num].tz = tz;
			objects[object_num].sx = size * 1;
			objects[object_num].sy = size * 1;
			objects[object_num].sz = size * 3;
			objects[object_num].ry = angle;
			objects[object_num].r = 0.75;
			objects[object_num].g = 0.75;
			objects[object_num].b = 0.75;
			objects[object_num].NewObject = 'C';
		}
		//���� ������ ����
		{
			objects[object_num + 1].tx = 1;
			objects[object_num + 1].tz = tz;
			objects[object_num + 1].sx = size * 0.2;
			objects[object_num + 1].sy = size * 1.5;
			objects[object_num + 1].sz = size * 1.5;
			objects[object_num + 1].ry = angle;
			objects[object_num + 1].r = 0.75;
			objects[object_num + 1].g = 0.5;
			objects[object_num + 1].b = 0.0;
			objects[object_num + 1].NewObject = 'C';
		}
		//���� ���� ����
		{
			objects[object_num + 2].tx = -1;
			objects[object_num + 2].tz = tz;
			objects[object_num + 2].sx = size * 0.2;
			objects[object_num + 2].sy = size * 1.5;
			objects[object_num + 2].sz = size * 1.5;
			objects[object_num + 2].ry = angle;
			objects[object_num + 2].r = 0.75;
			objects[object_num + 2].g = 0.5;
			objects[object_num + 2].b = 0.0;
			objects[object_num + 2].NewObject = 'C';
		}
		object_num += 3;
	}
}

void make_cannonball(GLfloat tz, GLfloat size, GLfloat angle) {
	{
		objects[cannonball_num].tz = tz;
		objects[cannonball_num].sx = size;
		objects[cannonball_num].sy = size;
		objects[cannonball_num].sz = size;
		objects[cannonball_num].ry = angle;
		objects[cannonball_num].r = 0.8;
		objects[cannonball_num].g = 0.8;
		objects[cannonball_num].b = 0.8;
		objects[cannonball_num].NewObject = 'c';
	}
	{
		objects[cannonball_num + 1000].tz = tz;
		objects[cannonball_num + 1000].sx = 1;
		objects[cannonball_num + 1000].sy = 1;
		objects[cannonball_num + 1000].sz = 1;
		objects[cannonball_num + 1000].ry = angle;
		objects[cannonball_num + 1000].r = 0.8;
		objects[cannonball_num + 1000].g = 0.8;
		objects[cannonball_num + 1000].b = 0.8;
		objects[cannonball_num + 1000].NewObject = 'b';
	}
	cannonball_num += 1;
}

void cannon_setTransform(int idx) {  //�ش� model_count�� ĳ���� ��ȯ
	glm::mat4 S2 = glm::mat4(1.0f);//
	
	glm::mat4 R1 = glm::mat4(1.0f);//
	glm::mat4 R2 = glm::mat4(1.0f);//
	glm::mat4 R3 = glm::mat4(1.0f);//
	glm::mat4 R4 = glm::mat4(1.0f);//
	

	glm::mat4 T1 = glm::mat4(1.0f);//
	
	R1 = glm::rotate(R1, glm::radians(objects[idx].rx), glm::vec3(1.0, 0.0, 0.0)); //x�� ���� ���� //
	R2 = glm::rotate(R2, glm::radians(objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //y�� ���� ����//
	R3 = glm::rotate(R3, glm::radians(objects[idx].rz), glm::vec3(0.0, 0.0, 1.0)); //z�� ���� ����//
	R4 = glm::rotate(R4, glm::radians(-objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //z�� ���� ����//
	T1 = glm::translate(T1, glm::vec3(objects[idx].tx, objects[idx].ty, objects[idx].tz));//��ġ//
	S2 = glm::scale(S2, glm::vec3(objects[idx].sx, objects[idx].sy, objects[idx].sz));//ũ��//
	transformMatrix = R1 * R2 * R3 * T1 *  S2;
	transformMatrix2 = R1 * R2 * R3 * T1 * R4* S2;
}
