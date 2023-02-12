#pragma once

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT Vertex {
public:
    Vertex(QVector3D _position = QVector3D(0, 0, 0),
           QVector3D _normal = QVector3D(0, 0, 1),
           QVector3D _tangent = QVector3D(0, 1, 0),
           QVector3D _bitangent = QVector3D(1, 0, 0),
           QVector2D _texCoords = QVector2D(0, 0));
    Vertex(const Vertex &other);

    Vertex& operator=(const Vertex &other);
    bool operator==(const Vertex &other) const;

    QVector3D position;//坐标位置
    QVector3D normal;//法线
    QVector3D tangent;//切线
    QVector3D bitangent;//双切线
    QVector2D texCoords;//纹理坐标
};

Vertex operator*(QMatrix4x4 mat, const Vertex& vertex);
QDataStream &operator<<(QDataStream &out, const Vertex& vertex);
QDataStream &operator>>(QDataStream &in, Vertex& vertex);
