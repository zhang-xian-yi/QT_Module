#include "OpenGLTexture.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入

OpenGLTexture::OpenGLTexture(QSharedPointer<Texture> texture) {
    m_host = texture;
    m_openGLTexture = 0;

    if (m_host->property("OpenGLTexturePointer").isValid()) {
        if (logLV >= LOG_LEVEL_ERROR)
            dout << "FATAL: Multiple OpenGLTexture instances are bound to one texture";
        exit(-1);
    }
    m_host->setProperty("OpenGLTexturePointer", QVariant::fromValue(this));

    connect(m_host.get(), SIGNAL(imageChanged(QImage)), this, SLOT(imageChanged(QImage)));
    connect(m_host.get(), SIGNAL(destroyed(QObject*)), this, SLOT(hostDestroyed(QObject*)));
}

OpenGLTexture::~OpenGLTexture() {

    //不删除m_host 由传递方负责
    m_host->setProperty("OpenGLTexturePointer", QVariant());
}

void OpenGLTexture::create() {
    m_openGLTexture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(m_host->image().mirrored()));
    m_openGLTexture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_openGLTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_openGLTexture->setWrapMode(QOpenGLTexture::Repeat);
}

bool OpenGLTexture::bind() {
    if (!m_openGLTexture) create();
    if (!m_host->enabled()) return false;
    QOpenGLFunctions * glFuncs = QOpenGLContext::currentContext()->functions();
    if (m_host->textureType() == Texture::Diffuse) { // Diffuse map
        glFuncs->glActiveTexture(GL_TEXTURE0 + 0);
        glFuncs->glBindTexture(GL_TEXTURE_2D, m_openGLTexture->textureId());
    } else if (m_host->textureType() == Texture::Specular) { // Specular map
        glFuncs->glActiveTexture(GL_TEXTURE0 + 1);
        glFuncs->glBindTexture(GL_TEXTURE_2D, m_openGLTexture->textureId());
    } else if (m_host->textureType() == Texture::Bump) { // Bump map
        glFuncs->glActiveTexture(GL_TEXTURE0 + 2);
        glFuncs->glBindTexture(GL_TEXTURE_2D, m_openGLTexture->textureId());
    }
    return true;
}

void OpenGLTexture::release() {
    QOpenGLFunctions * glFuncs = QOpenGLContext::currentContext()->functions();
    if (m_host->textureType() == Texture::Diffuse) { // Diffuse map
        glFuncs->glActiveTexture(GL_TEXTURE0 + 0);
        glFuncs->glBindTexture(GL_TEXTURE_2D, 0);
    } else if (m_host->textureType() == Texture::Specular) { // Specular map
        glFuncs->glActiveTexture(GL_TEXTURE0 + 1);
        glFuncs->glBindTexture(GL_TEXTURE_2D, 0);
    } else if (m_host->textureType() == Texture::Bump) { // Bump map
        glFuncs->glActiveTexture(GL_TEXTURE0 + 2);
        glFuncs->glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void OpenGLTexture::imageChanged(const QImage& image) {
    if (m_openGLTexture) {
        m_openGLTexture.clear();
        m_openGLTexture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(image));
        m_openGLTexture->setMinificationFilter(QOpenGLTexture::Nearest);
        m_openGLTexture->setMagnificationFilter(QOpenGLTexture::Linear);
        m_openGLTexture->setWrapMode(QOpenGLTexture::Repeat);
    }
}

void OpenGLTexture::hostDestroyed(QObject *) {
    // Commit suicide
    delete this;
}
