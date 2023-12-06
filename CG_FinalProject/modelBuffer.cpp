// 모델 버퍼 
#include "buffer.h"
#include "sphere.h"

std::vector<Vertex> vertices;
GLuint vertexCount = loadObj("sphere.obj", vertices);

GLfloat vertexCube[] = { // 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,		 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,			 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,		 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,		 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

GLuint VAO[MODEL_COUNT], VBO;  // MODEL_COUNT는 config.h에 정의되어있음

void vertexInput(int idx) {  // vertex
	switch (idx) {  // 여기에 노말값이 담긴 버텍스 데이터 추가
	case 0:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCube), vertexCube, GL_STATIC_DRAW);
		break;
	case 1:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCube), vertexCube, GL_STATIC_DRAW);
		break;
	}
	if(2000>idx&& idx >= 1000)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	else if(2000 <= idx)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCube), vertexCube, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCube), vertexCube, GL_STATIC_DRAW);

}

void setBuffer(int idx, int bufferMode) {
	if (2000>idx&& idx >= 1000) {
		glGenVertexArrays(1, &VAO[idx]);
		glBindVertexArray(VAO[idx]);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		vertexInput(idx);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(1);
		return;
	}

	if (bufferMode == modeInit) {  // bufferMode == modeUpdate 라면 해당 부분은 실행하지 않음
		glGenVertexArrays(1, &VAO[idx]);
		glBindVertexArray(VAO[idx]);
		glGenBuffers(1, &VBO);
	}

	if (bufferMode == modeInit || bufferMode == modeUpdate) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		vertexInput(idx);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0); // 위치 속성
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // 노말 속성
		glEnableVertexAttribArray(1);
	}
}
