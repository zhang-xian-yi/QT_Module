#pragma once

#include "Material/Material.h"
#include "OpenGLUniformBufferObject.h"
#include "Texture/OpenGLTexture.h"

class OpenGLMaterial: public QObject {
    Q_OBJECT

public:
    OpenGLMaterial(QSharedPointer<Material> material, QObject* parent = 0);
    ~OpenGLMaterial();
    QSharedPointer<Material> host() const;

    void bind();
    void release();

private:
    QSharedPointer<Material> m_host;
    QSharedPointer<OpenGLTexture> m_openGLDiffuseTexture, m_openGLSpecularTexture, m_openGLBumpTexture;
    static QSharedPointer<OpenGLUniformBufferObject> m_materialInfo;

private slots:
    void diffuseTextureChanged(QSharedPointer<Texture> diffuseTexture);
    void specularTextureChanged(QSharedPointer<Texture> specularTexture);
    void bumpTextureChanged(QSharedPointer<Texture> bumpTexture);
    void hostDestroyed(QObject* host);
};
