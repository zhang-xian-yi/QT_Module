#pragma once
#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT Texture: public QObject {
    Q_OBJECT

public:
    enum TextureType {
        Diffuse = 0,
        Specular = 1,
        Bump = 2
    };

    Texture(TextureType textureType = Diffuse);
    Texture(const Texture& texture);
    ~Texture();

    void dumpObjectInfo(int level = 0);
    void dumpObjectTree(int level = 0);

    bool enabled() const;
    TextureType textureType() const;
    const QImage & image() const;

public slots:
    void setEnabled(bool enabled);
    void setTextureType(TextureType textureType);
    void setImage(const QImage& image);

signals:
    void enabledChanged(bool enabled);
    void textureTypeChanged(int textureType);
    void imageChanged(const QImage& image);

private:
    bool m_enabled;
    TextureType m_textureType;
    QImage m_image;
};

QDataStream &operator>>(QDataStream &in, Texture::TextureType& textureType);
