//#include "translate.h"
//
//void make_cannon(GLfloat tx, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat ry) {//�ҷ��� �� ���� ����
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
//void cannon_setTransform(int idx) {  //�ش� model_count�� ĳ���� ��ȯ
//	using namespace glm;
//	transformMatrix = mat4(1.0f);
//	switch (idx) {  // ��ȯ �߰� 
//	case 0:
//		//transformMatrix = glm::translate(transformMatrix, glm::vec3(1, 0, 0));//��ġ
//		transformMatrix = glm::scale(transformMatrix, glm::vec3(1, 1, 3));//��ġ
//		break;
//	case 1:
//		transformMatrix = glm::translate(transformMatrix, glm::vec3(1, 0, 0));//��ġ
//		transformMatrix = glm::scale(transformMatrix, glm::vec3(0.2, 1.5, 1.5));//��ġ
//		break;
//	}
//}
//
//void cannon_modelOutput(int idx) {  // �� ��� 
//	unsigned int objColorLocation = glGetUniformLocation(ID, "objectColor"); //����
//	switch (idx) {
//	case 0:
//		glUniform3f(objColorLocation, 1, 0.5, 0.5);
//		glDrawArrays(GL_TRIANGLES, 0, 36);  // ť�� ���
//		break;
//	case 1:
//		glDrawArrays(GL_TRIANGLES, 0, 36);  // ť�� ���
//		break;
//
//	}
//}
