#pragma once

#include "Scene/OpenGLScene.h"

class OpenGLRenderer: public QObject {
    Q_OBJECT

public:
    OpenGLRenderer(QObject* parent = 0);
    OpenGLRenderer(const OpenGLRenderer& renderer);

    bool hasErrorLog();
    QString errorLog();

    bool reloadShaders();
    void reloadFrameBuffers();

    uint32_t pickingPass(QSharedPointer<OpenGLScene> openGLScene, QPoint cursorPos);
    void render(QSharedPointer<OpenGLScene> openGLScene);

private:
    QString m_log;
    QOpenGLShaderProgram *m_basicShader, *m_pickingShader, *m_phongShader;
    QSharedPointer<QOpenGLFramebufferObject> m_pickingPassFBO;

    QOpenGLShaderProgram * loadShaderFromFile(
        QString vertexShaderFilePath,
        QString fragmentShaderFilePath,
        QString geometryShaderFilePath = "");
};
