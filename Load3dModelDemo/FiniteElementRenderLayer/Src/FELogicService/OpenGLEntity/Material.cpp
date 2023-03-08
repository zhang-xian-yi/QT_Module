#include "Material.h"

Material::Material()
{
    ambient = 0.0f;//环境光
    diffuse = 0.9f;//漫反射
    specular = 0.5f;//镜面反射，值越大，越闪亮
    shininess = 16;//值越大光斑越亮
}

Material::Material(float ambient, float diffuse, float spec, float shinnes)
{
    ambient = ambient;//环境光
    diffuse = diffuse;//漫反射
    specular = spec;//镜面反射，值越大，越闪亮
    shininess = shinnes;//值越大光斑越亮
}

QVector4D Material::GetData()
{
    QVector4D ret;
    ret.setX(ambient);
    ret.setY(diffuse);
    ret.setZ(specular);
    ret.setW(shininess);
    return ret;
}
