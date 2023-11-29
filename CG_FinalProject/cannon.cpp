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
	objects[cannonball_num].tz = tz;
	objects[cannonball_num].sx = size;
	objects[cannonball_num].sy = size;
	objects[cannonball_num].sz = size;
	objects[cannonball_num].ry = angle;
	objects[cannonball_num].r = 0.8;
	objects[cannonball_num].g = 0.8;
	objects[cannonball_num].b = 0.8;
	objects[cannonball_num].NewObject = 'c';
	cannonball_num += 1;
}

void cannon_setTransform(int idx) {  //�ش� model_count�� ĳ���� ��ȯ
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rx), glm::vec3(1.0, 0.0, 0.0)); //x�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //y�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rz), glm::vec3(0.0, 0.0, 1.0)); //z�� ���� ����
	transformMatrix = glm::translate(transformMatrix, glm::vec3(objects[idx].tx, objects[idx].ty, objects[idx].tz));//��ġ
	transformMatrix = glm::scale(transformMatrix, glm::vec3(objects[idx].sx, objects[idx].sy, objects[idx].sz));//ũ��
}
