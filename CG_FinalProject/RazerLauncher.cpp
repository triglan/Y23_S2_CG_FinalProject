#include "translate.h"
#include "config.h"
#include "objects.h"

void make_razerLauncher(GLfloat tz, GLfloat size, GLfloat angle) {//�ҷ��� �� ���� ����
	if (object_num < 100000 - 3) {
		//������ �߻�� ����
		{//tz�� -������ �־�� �ڿ��� ������ ������ �ٶ󺸰� ����
			objects[object_num].tz = tz;
			objects[object_num].sx = size * 1;
			objects[object_num].sy = size * 1;
			objects[object_num].sz = size * 2;
			objects[object_num].ry = angle;
			objects[object_num].r = 0.25;
			objects[object_num].g = 0.25;
			objects[object_num].b = 0.25;
			objects[object_num].NewObject = true;
		}
		//������ �Ӹ�
		{
			objects[object_num + 1].ty = 0.75;
			objects[object_num + 1].tz = tz;
			objects[object_num + 1].sx = size * 0.5;
			objects[object_num + 1].sy = size * 0.5;
			objects[object_num + 1].sz = size * 0.5;
			objects[object_num + 1].ry = angle;
			objects[object_num].r = 1;
			objects[object_num].g = 0.15;
			objects[object_num].b = 0.15;
			objects[object_num + 1].NewObject = true;
		}
		object_num += 2;
	}
}

void razerLauncher_setTransform(int idx) {  //�ش� model_count�� ĳ���� ��ȯ
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rx), glm::vec3(1.0, 0.0, 0.0)); //x�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //y�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rz), glm::vec3(0.0, 0.0, 1.0)); //z�� ���� ����
	transformMatrix = glm::translate(transformMatrix, glm::vec3(objects[idx].tx, objects[idx].ty, objects[idx].tz));//��ġ
	transformMatrix = glm::scale(transformMatrix, glm::vec3(objects[idx].sx, objects[idx].sy, objects[idx].sz));//ũ��
}
