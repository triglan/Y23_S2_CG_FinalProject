#include "sphere.h"

GLuint loadObj(const char* filename, std::vector<Vertex>& vertices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open obj file: " << filename << std::endl;
        return 0;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords; // 추가된 부분

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;

            positions.push_back(position);
        }
        else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;

            normals.push_back(normal);
        }
        else if (type == "vt") { // 추가된 부분
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;

            texCoords.push_back(texCoord);
        }
        else if (type == "f") {
            for (int i = 0; i < 3; ++i) {
                std::string vertex;
                iss >> vertex;
                std::istringstream vertexStream(vertex);
                std::string indexStr;
                std::getline(vertexStream, indexStr, '/');
                int index = std::stoi(indexStr) - 1;
                Vertex v;
                v.position = positions[index];
                std::getline(vertexStream, indexStr, '/');
                if (!indexStr.empty()) {
                    int texCoordIndex = std::stoi(indexStr) - 1;
                    v.texCoords = texCoords[texCoordIndex];
                }
                std::getline(vertexStream, indexStr, '/');
                if (!indexStr.empty()) {
                    int normalIndex = std::stoi(indexStr) - 1;
                    v.normal = normals[normalIndex];
                }
                vertices.push_back(v);
            }
        }
    }

    return vertices.size();
}