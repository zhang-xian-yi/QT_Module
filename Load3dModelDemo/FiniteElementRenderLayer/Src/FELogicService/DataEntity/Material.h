#ifndef MATERIAL_H
#define MATERIAL_H

//光材质，影响光影效果

class Material
{
public:
    Material();
    Material(float ambient,float diffuse,float spec,float shinnes);
    QVector4D GetData();
public:
    float ambient ;//环境光
    float diffuse ;//漫反射
    float specular;//镜面反射，值越大，越闪亮
    float shininess;//值越大光斑越亮
};

#endif // MATERIAL_H
