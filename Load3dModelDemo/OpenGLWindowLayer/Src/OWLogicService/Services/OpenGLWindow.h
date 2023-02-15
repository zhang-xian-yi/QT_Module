#pragma once

#include "Scene/OpenGLScene.h"
#include "OpenGLRenderer.h"

class OpenGLWindow: public QOpenGLWidget{
    Q_OBJECT

public:
    OpenGLWindow();
    ~OpenGLWindow();
    OpenGLWindow(QSharedPointer<OpenGLScene> openGLScene, QSharedPointer<OpenGLRenderer> renderer);

    void setScene(QSharedPointer<OpenGLScene> openGLScene);
    void setRenderer(QSharedPointer<OpenGLRenderer> renderer);
    void setEnableMousePicking(bool enabled);
    void setCustomRenderingLoop(void (*customRenderingLoop)(QSharedPointer<Scene>));
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
    QSharedPointer<OpenGLScene>    m_openGLScene;
    QSharedPointer<OpenGLRenderer> m_renderer;
    void (*m_customRenderingLoop)(QSharedPointer<Scene> p);

    void processUserInput();
    void configSignals();

private slots:
    void sceneDestroyed(QObject* host);
};
