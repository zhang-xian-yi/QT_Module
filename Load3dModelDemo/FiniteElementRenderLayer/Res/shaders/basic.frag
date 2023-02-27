#version 330 core
out vec4 outColor;
struct Material {
float ambient;
float diffuse;
float specular;
float shininess;
};
struct Light {
    vec3 position;
    vec3 color;
};
in vec3 vColor;
in vec3 vNormal;
in vec3 FragPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
void main()
{
    float ambient = material.ambient;
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    float diffuse = material.diffuse * diff;
    float spec = 0;
    if (diff > 0)
    {
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    }
    float specular = material.specular * spec;
    // final
    vec3 result = (ambient + diffuse) * vColor * light.color + specular * light.color;
    outColor = vec4(result,1.0f);
}
