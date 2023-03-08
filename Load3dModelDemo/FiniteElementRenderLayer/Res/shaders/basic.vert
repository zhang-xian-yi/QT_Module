#version 330 core
in vec4 vPosition;
in vec3 aColor;
in vec3 aNormal;
out vec3 vColor;
out vec3 vNormal;
out vec3 FragPos;
uniform mat4 mvp_matrix;
void main()
{
    gl_Position = mvp_matrix * vPosition;
    FragPos = vec3(vPosition);
    vNormal = mat3(transpose(inverse(mvp_matrix))) * aNormal;
    vColor = aColor;
}
