// 모델 변환 
#include "translate.h"
#include "config.h"
#include "cannon.h"
#include "RazerLauncher.h"
#include "Razer.h"
#include "sphere.h"

//모델 좌표 cpp파일은 여기에 임포트 -> ex) #include "cube_ebo.cpp"

extern GLuint ID;
extern GLuint VAO[MODEL_COUNT];  // MODEL_COUNT는 config.h에 정의되어있음



void finishTransform(int idx) {  // 변환 전달 
	projectionLocation = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	viewLocation = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	lightPosLocation = glGetUniformLocation(ID, "lightPos"); // lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);

	lightColorLocation = glGetUniformLocation(ID, "lightColor"); // lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

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
		projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);
		break;
	case modeOrtho:
		projection = ortho(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 100.0f);
		break;
	}
}
void setLight() {  // 조명 세팅
	using namespace glm;
	lightMatrix = mat4(1.0f);
	lightPos = vec3(0.0f, 0.0f, 3.0f);  // 조명 위치
	vec3 initialLightPos = vec3(lightPos.x, lightPos.y, lightPos.z);
	lightPos = lightMatrix * vec4(initialLightPos, 1.0f);
}

void setTransform(int idx) {  // 변환 세팅
	//using namespace glm;
	transformMatrix = glm::mat4(1.0f);

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
	case 'c'://캐논 볼
	{
		cannon_setTransform(idx);
		break;
	}
	}
}

void modelOutput(int idx) {  // 모델 출력 
	if (objects[idx].NewObject != '0') {
		glUniform3f(objColorLocation, objects[idx].r, objects[idx].g, objects[idx].b);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix));
		if (idx >= 1000)
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		else
			glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	switch (idx) {
	case 200:
		break;
	}
}
