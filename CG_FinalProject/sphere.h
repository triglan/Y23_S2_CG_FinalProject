#pragma once
#include "config.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords; // 추가된 부분

 };


GLuint loadObj(const char* filename, std::vector<Vertex>& vertices);

extern std::vector<Vertex> vertices;
extern GLuint vertexCount;
