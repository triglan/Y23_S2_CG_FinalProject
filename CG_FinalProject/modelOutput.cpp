// 모델 변환 
#include "translate.h"
#include "config.h"
#include "cannon.h"
#include "RazerLauncher.h"
#include "Razer.h"
#include "sphere.h"
#include "soundController.cpp"

bool bgmStop, bgmPlay;

bool crash(glm::mat4 box1, glm::mat4 box2);

extern GLuint ID;
extern GLuint VAO[MODEL_COUNT];  // MODEL_COUNT는 config.h에 정의되어있음


glm::mat4 robot_body_transfrom;
glm::mat4 robot_legR_transfrom;
glm::mat4 robot_legL_transfrom;
glm::mat4 robot_face_transfrom;
glm::mat4 robot_armR_transfrom;
glm::mat4 robot_armL_transfrom;
glm::mat4 robot_dir_transfrom;
glm::mat4 robot_bb;
glm::mat4 box_transfrom;
glm::mat4 box_bb;

float go_lr = 0;//좌우이동
float go_fb = 0;//앞뒤이동
float go_jump = 0;
float robot_screw_angle = 0;//로봇 방향 바꿀때의 각도
float robot_arm_angle = 0;//팔 다리 움직일때 각도

void finishTransform(int idx) {  // 변환 전달 
	projectionLocation = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	viewLocation = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	lightPosLocation = glGetUniformLocation(ID, "lightPos"); // lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);

	lightColorLocation = glGetUniformLocation(ID, "lightColor"); // lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, lightColor[0], lightColor[1], lightColor[2]);

	objColorLocation = glGetUniformLocation(ID, "objectColor"); // object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, 0.5, 0.5, 0.5);

	viewPosLocation = glGetUniformLocation(ID, "viewPos"); // viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

	modelLocation = glGetUniformLocation(ID, "model"); // 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix)); // modelTransform 변수에 변환 값 적용하기

	glBindVertexArray(VAO[idx]);  // 각 모델마다 지정된 VAO만 사용
}
void setCamera() {  // 카메라 세팅
	using namespace glm;
	view = mat4(1.0f);
	cameraPos = vec3(3.0f, 5.0f, 20.0f);
	cameraDirection = vec3(0.0f, 0.0f, 0.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);
	view = lookAt(cameraPos, cameraDirection, cameraUp);
}
void setProjection(int projectionMode) {  // 투영 세팅
	using namespace glm;
	projection = mat4(1.0f);
	switch (projectionMode) {
	case modePers:
		projection = perspective(radians(45.0f), 1.0f, 0.1f, 200.0f);
		break;
	case modeOrtho:
		projection = ortho(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 200.0f);
		break;
	}
}
void setLight() {  // 조명 세팅
	using namespace glm;
	lightMatrix = mat4(1.0f);
	lightMatrix = glm::rotate(lightMatrix, glm::radians(SunAngle), glm::vec3(0.0, 0.0, 1.0)); //y축 기준 자전
	lightMatrix = glm::translate(lightMatrix, glm::vec3(0.0f, 8.0f, 0.0f));//크기
	lightPos = vec3(0.0f, 0.0f, 0.0f);  // 조명 위치
	vec3 initialLightPos = vec3(lightPos.x, lightPos.y, lightPos.z);
	lightPos = lightMatrix * vec4(initialLightPos, 1.0f);
}

void setTransform(int idx) {  // 변환 세팅
	//using namespace glm;
	transformMatrix = glm::mat4(1.0f);

	switch (idx) {  // 변환 추가 
	case 0:
	{
		glm::mat4 T1 = glm::mat4(1.0f);
		glm::mat4 T2 = glm::mat4(1.0f);
		glm::mat4 T3 = glm::mat4(1.0f);
		glm::mat4 T4 = glm::mat4(1.0f);
		glm::mat4 T5 = glm::mat4(1.0f);
		glm::mat4 T6 = glm::mat4(1.0f);
		glm::mat4 T7 = glm::mat4(1.0f);
		glm::mat4 T8 = glm::mat4(1.0f);
		glm::mat4 T_lrfbj = glm::mat4(1.0f);

		glm::mat4 S1 = glm::mat4(1.0f);
		glm::mat4 S2 = glm::mat4(1.0f);
		glm::mat4 S3 = glm::mat4(1.0f);
		glm::mat4 S4 = glm::mat4(1.0f);
		glm::mat4 S5 = glm::mat4(1.0f);

		glm::mat4 R1 = glm::mat4(1.0f);
		glm::mat4 R2 = glm::mat4(1.0f);
		glm::mat4 R3 = glm::mat4(1.0f);
		glm::mat4 restoration = glm::mat4(1.0f);


		S1 = glm::scale(S1, glm::vec3(0.4, 0.6, 0.4));
		S2 = glm::scale(S2, glm::vec3(0.3, 0.3, 0.3));
		S3 = glm::scale(S3, glm::vec3(0.1, 0.4, 0.1));
		S4 = glm::scale(S4, glm::vec3(0.2, 0.2, 0.2));
		S5 = glm::scale(S5, glm::vec3(0.2 + 0.5, 0.2 + 0.8, 0.2 + 0.5));

		T1 = glm::translate(T1, glm::vec3(0, 0.4, 0));
		T2 = glm::translate(T2, glm::vec3(0.3, 0.1, 0));
		T3 = glm::translate(T3, glm::vec3(-0.3, 0.1, 0));
		T4 = glm::translate(T4, glm::vec3(0.1, -0.5, 0));
		T5 = glm::translate(T5, glm::vec3(-0.1, -0.5, 0));
		T6 = glm::translate(T6, glm::vec3(0.0, 0.4, 0.2));
		T7 = glm::translate(T7, glm::vec3(0.0, -0.2, 0));
		T8 = glm::translate(T8, glm::vec3(0.0, 0.2, 0));
		T_lrfbj = glm::translate(T_lrfbj, glm::vec3(go_lr, go_jump, go_fb));
		//restoration= glm::rotate(restoration, glm::radians(robot_screw_angle), glm::vec3(0.0, 1, 0.0));

		R1 = glm::rotate(R1, glm::radians(robot_screw_angle), glm::vec3(0.0, 1, 0.0));
		R2 = glm::rotate(R2, glm::radians(robot_arm_angle), glm::vec3(1.0, 0.0, 0.0));
		R3 = glm::rotate(R3, glm::radians(-robot_arm_angle), glm::vec3(1.0, 0.0, 0.0));


		robot_body_transfrom = T_lrfbj * R1 * S1;
		robot_face_transfrom = T_lrfbj * R1 * T1 * S2;
		robot_armR_transfrom = T_lrfbj * R1 * T2 * T8 * R2 * T7 * S3;//T8*R2*T7팔 돌리기 
		robot_armL_transfrom = T_lrfbj * R1 * T3 * T8 * R3 * T7 * S3;
		robot_legR_transfrom = T_lrfbj * R1 * T4 * T8 * R3 * T7 * S3;
		robot_legL_transfrom = T_lrfbj * R1 * T5 * T8 * R2 * T7 * S3;
		robot_dir_transfrom = T_lrfbj * R1 * T6 * S4;
		robot_bb = T_lrfbj * S5;
		break;
	}

	case 1:
	{
		glm::mat4 S1_1 = glm::mat4(1.0f);
		S1_1 = glm::scale(S1_1, glm::vec3(0.4, 0.4, 0.4));
		box_transfrom = S1_1;
		break;
	}

	case 30: // TODO :: 바닥
	{
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0, -1, 0));//위치
		transformMatrix = glm::scale(transformMatrix, glm::vec3(15, 0.1, 15));//크기

		break;
	}
	case 31: // TODO :: 바다
	{
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0, -2, 0));//위치
		transformMatrix = glm::scale(transformMatrix, glm::vec3(100, 0.1, 100));//크기

		break;
	}
	case 32: // TODO :: 태양
	{
		transformMatrix = glm::rotate(transformMatrix, glm::radians(SunAngle), glm::vec3(0.0, 0.0, 1.0)); //z축 기준 자전
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0, 8.f, 0));//위치
		transformMatrix = glm::scale(transformMatrix, glm::vec3(1, 1, 1));//크기

		break;
	}
	case 33: // TODO :: 벽
	{
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0.f, 0.f, -100.f));//위치
		transformMatrix = glm::scale(transformMatrix, glm::vec3(200, 200, 1));//크기

		break;
	}
	}

	switch (objects[idx].NewObject) {
	case 'C'://대문자 C는 발사대 변화
	{
		cannon_setTransform(idx);
		break;
	}
	case 'R'://
	{
		razerLauncher_setTransform(idx);
		break;
	}
	case 'r'://
	{
		razer_setTransform(idx);
		break;
	}
	case 'c': case 'b'://캐논 볼
	{
		cannon_setTransform(idx);
		break;
	}
	}
}

void modelOutput(int idx) {  // 모델 출력 
	switch (idx) {
	case 0:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_body_transfrom)); // modelTransform 변수에 변환 값 적용하기
		glDrawArrays(GL_TRIANGLES, 0, 36);  // 큐브 출력
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_face_transfrom)); // modelTransform
		glDrawArrays(GL_TRIANGLES, 0, 36);  //
		glUniform3f(objColorLocation, 1, 0.5, 0.5);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_armR_transfrom)); // modelTransform
		glDrawArrays(GL_TRIANGLES, 0, 36);  //
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_armL_transfrom)); // modelTransform
		glDrawArrays(GL_TRIANGLES, 0, 36);  //
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_legR_transfrom)); // modelTransform
		glDrawArrays(GL_TRIANGLES, 0, 36);  //
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_legL_transfrom)); // modelTransform
		glDrawArrays(GL_TRIANGLES, 0, 36);  //
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_dir_transfrom)); // modelTransform
		glDrawArrays(GL_TRIANGLES, 0, 36);  //
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(robot_bb)); // modelTransform
		//glDrawArrays(GL_TRIANGLES, 0, 36);  //

		break;
	}


	case 30: // TODO :: 모래
	{
		glUniform3f(objColorLocation, 0.95, 0.95, 0.7);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
	case 31: // TODO :: 바다
	{
		glUniform3f(objColorLocation, 0.2, 0.2, 0.9);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
	case 32: // TODO :: 태양
	{
		glUniform3f(objColorLocation, 0.9, 0.2, 0.2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
	case 33: // TODO :: 벽
	{
		glUniform3f(objColorLocation, 0.2, 0.2, 0.6);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		break;
	}
	}
	
	if (objects[idx].NewObject != '0') {
		glUniform3f(objColorLocation, objects[idx].r, objects[idx].g, objects[idx].b);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix2));
		if (2000 > idx && idx >= 1000)
		{
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		}
		else if (2000 <= idx&& idx<3000)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix2));
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			if (crash(transformMatrix2, robot_bb)) {
				lightColor[0] = 0.2, lightColor[1] = 0.2, lightColor[2] = 0.2;
				resume_game = false;
				bgmStop = true;
			}//
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			if (crash(transformMatrix, robot_bb) 
				&& (100 < objects[idx].lifetime && objects[idx].lifetime < 200)) {
					lightColor[0] = 0.2, lightColor[1] = 0.2, lightColor[2] = 0.2;
					resume_game = false;
					bgmStop = true;
			}
		}
	}

}

bool crash(glm::mat4 box1, glm::mat4 box2)
{
	glm::vec4 position1_LT(-0.5, 0.5f, -0.5f, 1.0f);
	glm::vec4 position1_RT(0.5, 0.5f, -0.5f, 1.0f);
	glm::vec4 position1_LB(-0.5, 0.5f, 0.5f, 1.0f);
	glm::vec4 position1_RB(0.5, 0.5f, 0.5f, 1.0f);
	glm::vec4 position1_up(-0.5, 0.5f, -0.5f, 1.0f);
	glm::vec4 position1_down(-0.5, -0.5f, -0.5f, 1.0f);
	position1_LT = box1 * position1_LT;
	position1_LB = box1 * position1_LB;
	position1_RT = box1 * position1_RT;
	position1_RB = box1 * position1_RB;
	position1_up = box1 * position1_up;
	position1_down = box1 * position1_down;
	glm::vec4 position2_LT(-0.5, 0.5f, -0.5f, 1.0f);
	glm::vec4 position2_RT(0.5, 0.5f, -0.5f, 1.0f);
	glm::vec4 position2_LB(-0.5, 0.5f, 0.5f, 1.0f);
	glm::vec4 position2_RB(0.5, 0.5f, 0.5f, 1.0f);
	glm::vec4 position2_up(-0.5, 0.5f, -0.5f, 1.0f);
	glm::vec4 position2_down(-0.5, -0.5f, -0.5f, 1.0f);
	position2_LT = box2 * position2_LT;
	position2_LB = box2 * position2_LB;
	position2_RT = box2 * position2_RT;
	position2_up = box2 * position2_up;
	position2_down = box2 * position2_down;



	if (position1_RT.x<position2_LT.x || position1_LT.x > position2_RT.x
		|| position1_LT.z > position2_LB.z || position1_LB.z < position2_LT.z || position1_up.y < position2_down.y
		|| position2_up.y < position1_down.y)
	{
		//printf("충돌x\n");
		return false;
	}
	else
	{
		printf("충돌 1");
		return true;
	}

}

