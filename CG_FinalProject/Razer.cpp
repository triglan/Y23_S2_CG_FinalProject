#include "translate.h"
#include "config.h"
#include "objects.h"

void make_razer(GLfloat tz, GLfloat size, GLfloat tx) {//�ҷ��� �� ���� ����
	if (object_num < 100000 - 3) {
		//������ �߻�� ����
		{//tz�� -������ �־�� �ڿ��� ������ ������ �ٶ󺸰� ����
			objects[object_num].tz = tz;
			objects[object_num].tx = tx;
			objects[object_num].sx = size * 0.1;
			objects[object_num].sy = size * 0.1;
			objects[object_num].sz = size * 20;
			objects[object_num].r = 1.0;
			objects[object_num].g = 0.1;
			objects[object_num].b = 0.1;
			objects[object_num].NewObject = true;
			objects[object_num].NewObject = 'r';
		}
		object_num += 3;
	}
}

void razer_setTransform(int idx) {  //�ش� model_count�� ĳ���� ��ȯ
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rx), glm::vec3(1.0, 0.0, 0.0)); //x�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //y�� ���� ����
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rz), glm::vec3(0.0, 0.0, 1.0)); //z�� ���� ����
	transformMatrix = glm::translate(transformMatrix, glm::vec3(objects[idx].tx, objects[idx].ty, objects[idx].tz));//��ġ
	transformMatrix = glm::scale(transformMatrix, glm::vec3(objects[idx].sx, objects[idx].sy, objects[idx].sz));//ũ��
}
