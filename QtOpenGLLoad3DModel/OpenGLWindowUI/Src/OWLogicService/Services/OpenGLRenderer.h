#pragma once

#include "OpenGLWindowUI/Src/OWLogicService/OpenGLEntity/OpenGLScene.h"

class OpenGLRenderer:public QObject,protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLRenderer(QObject* parent = 0);
    OpenGLRenderer(const OpenGLRenderer& renderer);

    bool hasErrorLog();
    QString errorLog();

    bool reloadShaders();
    void reloadFrameBuffers();

    uint32_t pickingPass(OpenGLScene* openGLScene, QPoint cursorPos);
    void render(OpenGLScene* openGLScene);

private:
    QString m_log;
    QOpenGLShaderProgram *m_basicShader, *m_pickingShader, *m_phongShader;
    QOpenGLFramebufferObject *m_pickingPassFBO;

    QOpenGLShaderProgram * loadShaderFromFile(
        QString vertexShaderFilePath,
        QString fragmentShaderFilePath,
        QString geometryShaderFilePath = "");
};
