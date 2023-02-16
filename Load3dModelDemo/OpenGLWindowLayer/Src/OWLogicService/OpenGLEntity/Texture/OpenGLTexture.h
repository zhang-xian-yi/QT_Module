#pragma once

#include "Texture/Texture.h"

class OpenGLTexture: public QObject {
    Q_OBJECT

public:
    OpenGLTexture(QSharedPointer<Texture> texture);
    ~OpenGLTexture();

    void create();
    bool bind();
    void release();

private:
    QSharedPointer<Texture> m_host;
    QSharedPointer<QOpenGLTexture> m_openGLTexture;

private slots:
    void imageChanged(const QImage& image);
    void hostDestroyed(QObject* host);
};
