#include "translate.h"
#include "config.h"
#include "objects.h"

void make_razer(GLfloat tz, GLfloat size, GLfloat tx) {//불러올 때 마다 생성
	if (object_num < 100000 - 3) {
		//레이저 발사대 몸통
		{//tz는 -값으로 넣어야 뒤에서 대포가 정면을 바라보고 있음
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

void razer_setTransform(int idx) {  //해당 model_count의 캐논의 변환
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rx), glm::vec3(1.0, 0.0, 0.0)); //x축 기준 자전
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].ry), glm::vec3(0.0, 1.0, 0.0)); //y축 기준 자전
	transformMatrix = glm::rotate(transformMatrix, glm::radians(objects[idx].rz), glm::vec3(0.0, 0.0, 1.0)); //z축 기준 자전
	transformMatrix = glm::translate(transformMatrix, glm::vec3(objects[idx].tx, objects[idx].ty, objects[idx].tz));//위치
	transformMatrix = glm::scale(transformMatrix, glm::vec3(objects[idx].sx, objects[idx].sy, objects[idx].sz));//크기
}
