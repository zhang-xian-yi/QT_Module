#ifndef QtOpenGLWindow_H
#define QtOpenGLWindow_H

#include "OpenGLWindowUI/Src/OWLogicService/OpenGLEntity/OpenGLScene.h"
#include "OpenGLRenderer.h"
#include "FPSCounter.h"

namespace OpenGLWinNS {

    class QtOpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
    {
        Q_OBJECT
    public:
        virtual ~QtOpenGLWindow();
    public:
        QtOpenGLWindow(QWidget *parent = nullptr);

        void setScene(OpenGLScene* openGLScene);
        void setRenderer(OpenGLRenderer* renderer);
        void setEnableMousePicking(bool enabled);
        void setCustomRenderingLoop(void (*customRenderingLoop)(Scene*));
    protected:
        virtual void initializeGL() override;
        virtual void resizeGL(int w, int h) override;
        virtual void paintGL() override;

    protected slots:
        void onRenderTimerShot();

    protected:
        QTimer* m_pTimer;
    private:
        QHash<int, bool> m_keyPressed;
        QPoint m_lastCursorPos;
        QTime m_lastMousePressTime;
        bool m_enableMousePicking;
        OpenGLScene* m_openGLScene;
        OpenGLRenderer * m_renderer;
        FPSCounter* m_fpsCounter;
        void (*m_customRenderingLoop)(Scene*);
    };
}


#endif // QtOpenGLWindow_H
