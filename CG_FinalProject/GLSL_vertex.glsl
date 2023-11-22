#version 330 core

layout(location = 0) in vec3 inPosition; // ���� ��ġ attribute
layout(location = 1) in vec3 inNormal;   // ���� ���� attribute

out vec3 fragPos; // �����׸�Ʈ ���̴��� ������ ���� ��ġ
out vec3 normal;  // �����׸�Ʈ ���̴��� ������ ���� ����

uniform mat4 model;      // �� ���
uniform mat4 view;       // �� ���
uniform mat4 projection; // ���� ���

void main() {
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    fragPos = vec3(model * vec4(inPosition, 1.0));
    normal = vec3(transpose(inverse(model)) * vec4(inNormal, 1.0));
}
