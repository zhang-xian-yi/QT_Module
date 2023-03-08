#version 330 core
out vec4 glFragColor;

struct Material
{
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 color;
};

in vec3 vColor;
in vec3 vNormal;
in vec3 FragPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light1;

vec3 CalcLightResult(Light light)
{
    //漫反射
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.color * diff;
    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.color;
    // final 使用环境光效果不好
    return (material.ambient + diffuse + specular) * vColor;
}

void main()
{
    vec3 light1Result = CalcLightResult(light1);
    glFragColor = vec4(light1Result,1.0f);
}
