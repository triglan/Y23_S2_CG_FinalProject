#include "translate.h"
#include "config.h"
#include "objects.h"

void make_razerLauncher(GLfloat tz, GLfloat size, GLfloat tx) {//�ҷ��� �� ���� ����
	if (object_num < 100000 - 3) {
		//������ �߻�� ����
		{//tz�� -������ �־�� �ڿ��� ������ ������ �ٶ󺸰� ����
			objects[object_num].tx = tx;
			objects[object_num].tz = tz;
			objects[object_num].sx = size * 1;
			objects[object_num].sy = size * 1;
			objects[object_num].sz = size * 2;
			objects[object_num].r = 0.25;
			objects[object_num].g = 0.25;
			objects[object_num].b = 0.25;
			objects[object_num].NewObject = true;
			objects[object_num].NewObject = 'R';
		}
		//������ �Ӹ�
		{
			objects[object_num + 1].tx = tx;
			objects[object_num + 1].ty = 0.75;
			objects[object_num + 1].tz = tz;
			objects[object_num + 1].sx = size * 0.5;
			objects[object_num + 1].sy = size * 0.5;
			objects[object_num + 1].sz = size * 0.5;
			objects[object_num + 1].r = 0.15;
			objects[object_num + 1].g = 0.8;
			objects[object_num + 1].b = 0.15;
			objects[object_num + 1].NewObject = true;
			objects[object_num + 1].NewObject = 'R';
		}
		//������ �Ѿȱ�
		{
			objects[object_num + 2].tx = tx;
			objects[object_num + 2].ty = 0.0;
			objects[object_num + 2].tz = tz + 1;
			objects[object_num + 2].sx = size * 0.5;
			objects[object_num + 2].sy = size * 0.5;
			objects[object_num + 2].sz = size * 0.5;
			objects[object_num + 2].r = 1;
			objects[object_num + 2].g = 0.05;
			objects[object_num + 2].b = 0.05;
			objects[object_num + 2].NewObject = true;
			objects[object_num + 2].NewObject = 'R';
		}
		object_num += 3;
	}
}

void razerLauncher_setTransform(int idx) {  //�ش� model_count�� ĳ���� ��ȯ
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rx), glm::vec3(1.0, 0.0, 0.0)); //x�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //y�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rz), glm::vec3(0.0, 0.0, 1.0)); //z�� ���� ����
	transformMatrix = glm::translate(transformMatrix, glm::vec3(objects[idx].tx, objects[idx].ty, objects[idx].tz));//��ġ
	transformMatrix = glm::scale(transformMatrix, glm::vec3(objects[idx].sx, objects[idx].sy, objects[idx].sz));//ũ��
}
