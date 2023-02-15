#pragma once

#include "Scene/OpenGLScene.h"
#include "OpenGLRenderer.h"

class OpenGLWindow: public QOpenGLWidget{
    Q_OBJECT

public:
    OpenGLWindow();
    ~OpenGLWindow();
    OpenGLWindow(OpenGLScene* openGLScene, OpenGLRenderer* renderer);

    void setScene(OpenGLScene* openGLScene);
    void setRenderer(OpenGLRenderer* renderer);
    void setEnableMousePicking(bool enabled);
    void setCustomRenderingLoop(void (*customRenderingLoop)(Scene*));
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
protected:
    bool event(QEvent *ev) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
private:
    QHash<int, bool> m_keyPressed;
    QPoint m_lastCursorPos;
    QTime m_lastMousePressTime;
    bool m_enableMousePicking;
    OpenGLScene* m_openGLScene;
    OpenGLRenderer * m_renderer;
    void (*m_customRenderingLoop)(Scene*);

    void processUserInput();
    void configSignals();

private slots:
    void sceneDestroyed(QObject* host);
};
