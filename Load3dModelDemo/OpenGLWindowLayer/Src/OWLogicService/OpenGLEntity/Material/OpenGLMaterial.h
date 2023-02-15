#pragma once

#include "Material/Material.h"
#include "OpenGLUniformBufferObject.h"
#include "Texture/OpenGLTexture.h"

class OpenGLMaterial: public QObject {
    Q_OBJECT

public:
    OpenGLMaterial(Material* material, QObject* parent = 0);
    ~OpenGLMaterial();
    Material* host() const;

    void bind();
    void release();

private:
    Material* m_host;
    OpenGLTexture* m_openGLDiffuseTexture, *m_openGLSpecularTexture, *m_openGLBumpTexture;
    static OpenGLUniformBufferObject *m_materialInfo;

private slots:
    void diffuseTextureChanged(QSharedPointer<Texture> diffuseTexture);
    void specularTextureChanged(QSharedPointer<Texture> specularTexture);
    void bumpTextureChanged(QSharedPointer<Texture> bumpTexture);
    void hostDestroyed(QObject* host);
};
