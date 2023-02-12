#ifndef OW_PRECOMPLIE_H
#define OW_PRECOMPLIE_H
//暂时不添加拥有openGL特性的头文件进行预编译，不知为何此种编译方法会导致opengl相关的函数找不到标识符

// Add C++ includes here
#include "OpenGLWindowUI/Src/3rdLib/glad/glad.h"
#include "GLFW/glfw3.h"

// Add QT includes here
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QChildEvent>
#include <QFile>
#include <QFileInfo>
#include <QVariant>
#include <QMessageBox>

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>


#endif // OW_PRECOMPLIE_H
