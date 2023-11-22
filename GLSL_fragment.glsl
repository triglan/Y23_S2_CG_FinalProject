#version 330 core

in vec3 fragPos; // ���� ���̴��κ��� ���޹��� ���� ��ġ
in vec3 normal;  // ���� ���̴��κ��� ���޹��� ���� ����

out vec4 fragColor; // ���� ��� ����

uniform vec3 lightPos;    // ���� ��ġ
uniform vec3 viewPos;     // ī�޶� ��ġ
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // �ں��Ʈ
    float ambientLight = 0.5;
    vec3 ambient = ambientLight * lightColor;
    
    // ���� ���� ���
    vec3 lightDir = normalize(lightPos - fragPos);

    // ���� ���� ����ȭ
    vec3 normalVector = normalize(normal);

    // ��ǻ�� ���� ���
    float diff = max(dot(normalVector, lightDir), 0.0);
    vec3 diffuse = lightColor * diff;

    int shininess = 128;
    // ����ŧ�� ���� ���
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normalVector);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular =  spec * lightColor;

    // ���� ���� ���
    vec3 result = (ambient + diffuse + specular) * objectColor;

    // ���� ��� ���� ����
    fragColor = vec4(result, 1.0);
}
