//#include "translate.h"
//
//void make_cannon(GLfloat tx, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat ry) {//불러올 때 마다 생성
//	{
//		objects[MODEL_COUNT].tx = tx;
//
//	}
//	
//
//
//
//
//	MODEL_COUNT += 2;
//}
//
//void cannon_setTransform(int idx) {  //해당 model_count의 캐논의 변환
//	using namespace glm;
//	transformMatrix = mat4(1.0f);
//	switch (idx) {  // 변환 추가 
//	case 0:
//		//transformMatrix = glm::translate(transformMatrix, glm::vec3(1, 0, 0));//위치
//		transformMatrix = glm::scale(transformMatrix, glm::vec3(1, 1, 3));//위치
//		break;
//	case 1:
//		transformMatrix = glm::translate(transformMatrix, glm::vec3(1, 0, 0));//위치
//		transformMatrix = glm::scale(transformMatrix, glm::vec3(0.2, 1.5, 1.5));//위치
//		break;
//	}
//}
//
//void cannon_modelOutput(int idx) {  // 모델 출력 
//	unsigned int objColorLocation = glGetUniformLocation(ID, "objectColor"); //색깔
//	switch (idx) {
//	case 0:
//		glUniform3f(objColorLocation, 1, 0.5, 0.5);
//		glDrawArrays(GL_TRIANGLES, 0, 36);  // 큐브 출력
//		break;
//	case 1:
//		glDrawArrays(GL_TRIANGLES, 0, 36);  // 큐브 출력
//		break;
//
//	}
//}
