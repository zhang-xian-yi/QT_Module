#include "OpenGLMaterial.h"

struct ShaderMaterialInfo {
    QVector4D color;      // 16          // 0
    float ambient;        // 4           // 16
    float diffuse;        // 4           // 20
    float specular;       // 4           // 24
    float shininess;      // 4           // 28
    int useDiffuseMap;    // 4           // 32
    int useSpecularMap;   // 4           // 36
    int useBumpMap;       // 4           // 40
    int padding;          // 4           // 44
};

static ShaderMaterialInfo shaderMaterialInfo;

QSharedPointer<OpenGLUniformBufferObject> OpenGLMaterial::m_materialInfo = 0;

OpenGLMaterial::OpenGLMaterial(QSharedPointer<Material> material, QObject* parent): QObject(0) {
    m_host = material;

    this->diffuseTextureChanged(m_host->diffuseTexture());
    this->specularTextureChanged(m_host->specularTexture());
    this->bumpTextureChanged(m_host->bumpTexture());

    connect(m_host.get(), SIGNAL(diffuseTextureChanged(QSharedPointer<Texture>)), this, SLOT(diffuseTextureChanged(QSharedPointer<Texture>)));
    connect(m_host.get(), SIGNAL(specularTextureChanged(QSharedPointer<Texture>)), this, SLOT(specularTextureChanged(QSharedPointer<Texture>)));
    connect(m_host.get(), SIGNAL(bumpTextureChanged(QSharedPointer<Texture>)), this, SLOT(bumpTextureChanged(QSharedPointer<Texture>)));
    connect(m_host.get(), SIGNAL(destroyed(QObject*)), this, SLOT(hostDestroyed(QObject*)));

    //setParent(parent);
}

OpenGLMaterial::~OpenGLMaterial()
{

}

QSharedPointer<Material> OpenGLMaterial::host() const {
    return m_host;
}

void OpenGLMaterial::bind() {
    shaderMaterialInfo.useDiffuseMap = false;
    shaderMaterialInfo.useSpecularMap = false;
    shaderMaterialInfo.useBumpMap = false;

    if (m_openGLDiffuseTexture)
        shaderMaterialInfo.useDiffuseMap = m_openGLDiffuseTexture->bind();
    if (m_openGLSpecularTexture)
        shaderMaterialInfo.useSpecularMap = m_openGLSpecularTexture->bind();
    if (m_openGLBumpTexture)
        shaderMaterialInfo.useBumpMap = m_openGLBumpTexture->bind();

    shaderMaterialInfo.color = m_host->color();
    shaderMaterialInfo.ambient = m_host->ambient();
    shaderMaterialInfo.diffuse = m_host->diffuse();
    shaderMaterialInfo.specular = m_host->specular();
    shaderMaterialInfo.shininess = m_host->shininess();

    if (m_materialInfo == 0) {
        m_materialInfo = QSharedPointer<OpenGLUniformBufferObject>(new OpenGLUniformBufferObject);
        m_materialInfo->create();
        m_materialInfo->bind();
        m_materialInfo->allocate(MATERIAL_INFO_BINDING_POINT, NULL, sizeof(ShaderMaterialInfo));
        m_materialInfo->release();
    }
    m_materialInfo->bind();
    m_materialInfo->write(0, &shaderMaterialInfo, sizeof(ShaderMaterialInfo));
    m_materialInfo->release();
}

void OpenGLMaterial::release() {
    if (m_openGLDiffuseTexture) m_openGLDiffuseTexture->release();
    if (m_openGLSpecularTexture) m_openGLSpecularTexture->release();
    if (m_openGLBumpTexture) m_openGLBumpTexture->release();

    shaderMaterialInfo.color = QVector3D(0, 0, 0);
    shaderMaterialInfo.useDiffuseMap = 0;
    shaderMaterialInfo.useSpecularMap = 0;
    shaderMaterialInfo.useBumpMap = 0;

    if (m_materialInfo == 0) {
        m_materialInfo = QSharedPointer<OpenGLUniformBufferObject>(new OpenGLUniformBufferObject);
        m_materialInfo->create();
        m_materialInfo->bind();
        m_materialInfo->allocate(3, NULL, sizeof(ShaderMaterialInfo));
        m_materialInfo->release();
    }
    m_materialInfo->bind();
    m_materialInfo->write(0, &shaderMaterialInfo, sizeof(ShaderMaterialInfo));
    m_materialInfo->release();
}

void OpenGLMaterial::diffuseTextureChanged(QSharedPointer<Texture> diffuseTexture) {
    if (diffuseTexture.isNull())
    {
        m_openGLDiffuseTexture = nullptr;
    }
    else if (diffuseTexture->property("OpenGLTexturePointer").isValid())
    {
        m_openGLDiffuseTexture =diffuseTexture->property("OpenGLTexturePointer").value<QSharedPointer<OpenGLTexture>>();
    }
    else
    {
        m_openGLDiffuseTexture = QSharedPointer<OpenGLTexture>(new OpenGLTexture(diffuseTexture));
    }
}

void OpenGLMaterial::specularTextureChanged(QSharedPointer<Texture> specularTexture) {
    if (specularTexture.isNull())
    {
        m_openGLSpecularTexture = nullptr;
    }
    else if (specularTexture->property("OpenGLTexturePointer").isValid())
    {
        m_openGLSpecularTexture = specularTexture->property("OpenGLTexturePointer").value<QSharedPointer<OpenGLTexture>>();
    }
    else
    {
        m_openGLSpecularTexture = QSharedPointer<OpenGLTexture>(new OpenGLTexture(specularTexture));
    }
}

void OpenGLMaterial::bumpTextureChanged(QSharedPointer<Texture> bumpTexture) {
    if (bumpTexture.isNull())
    {
        m_openGLBumpTexture = nullptr;
    }
    else if (bumpTexture->property("OpenGLTexturePointer").isValid())
    {
        m_openGLBumpTexture = bumpTexture->property("OpenGLTexturePointer").value<QSharedPointer<OpenGLTexture>>();
    }
    else
    {
        m_openGLBumpTexture = QSharedPointer<OpenGLTexture>(new OpenGLTexture(bumpTexture));
    }
}

void OpenGLMaterial::hostDestroyed(QObject *) {
    // Commit suicide
    delete this;
}
