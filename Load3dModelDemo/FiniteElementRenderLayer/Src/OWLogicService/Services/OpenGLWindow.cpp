#include "OpenGlRender.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QtMath>
#include <QQuaternion>
#include "../Common/Src/ExtStruct.h"
namespace OpenGlRender
{

OpenGlRenderWin::OpenGlRenderWin(QWidget * parent) : QOpenGLWidget(parent)
      , cubeGeometry(0)
{
    this->m_MouseFlag = Qt::NoButton;
    this->m_MousePressFlag = false;
    this->m_xRot = 0;
    this->m_yRot = 0;
    this->m_zRot = 0;
    this->m_xTrans = 0;
    this->m_yTrans = 0;

    this->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());
}

OpenGlRenderWin::~OpenGlRenderWin()
{
    makeCurrent();
    delete  cubeGeometry;
    doneCurrent();
}

void OpenGlRenderWin::Rotate(QMatrix4x4 matrix)
{
    this->m_rotation = matrix;
    update();
}

void OpenGlRenderWin::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    this->cubeGeometry = CubeGeometry::GetInstance();

    Camera.distance = 5.0;
    Camera.fovy     = 5.0;
    Camera.zoom     = 1.0;
    //观察者位置在z轴负方向的位置上
    Camera.eye      = {0,0, Camera.zoom * Camera.distance};
    //被观察物体的中心坐标
    Camera.center   = {0.0,0.0,0.0};
    //观察者头部朝向y轴方向
    Camera.up       = {0.0,1.0,0.0};
    //依据上述定义，界面初始化后，从界面中看到的坐标系就是以界面中心为原点、水平向右为x轴正半轴、垂直向上为y轴正半轴、屏幕向内为z轴正半轴
}

//保证界面内物体的显示不受界面纵横比变化而变形
void OpenGlRenderWin::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.001, zFar = 1000.0;
    projection.setToIdentity();
    // 得到透视矩阵
    projection.perspective(Camera.fovy, aspect, zNear, zFar);
}

//缩放控制就是控制观察者的位置到被观察物体中心位置的距离，即改变Camera.eye的值
void OpenGlRenderWin::wheelEvent(QWheelEvent *event)
{
    if(this->m_MousePressFlag)
        return;
    if(event->angleDelta().y() > 0)
    {
        Camera.zoom -= 0.1;
    }else{
        Camera.zoom += 0.1;
    }
    if(Camera.zoom >= 3)
    {
        Camera.zoom = 3;
    }else if(Camera.zoom <= 0.1)
    {
        Camera.zoom = 0.1;
    }
    //因为我定义的观察者的位置是在z轴上，所以只改变Camera.eye的z值即可实现物体缩放效果
    Camera.eye.setZ(Camera.zoom * Camera.distance);
    update();
}
//用于记录按下鼠标的类型并记录鼠标按下时的位置
void OpenGlRenderWin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        this->m_MouseFlag = Qt::LeftButton;
    }else if(event->button() & Qt::RightButton)
    {
        this->m_MouseFlag = Qt::RightButton;
    }else if(event->button() & Qt::MidButton)
    {
        this->m_MouseFlag = Qt::MidButton;
    }
    this->m_MousePressFlag = true;
    this->mousePressPosition = event->pos();
}
//根据鼠标移动的量和鼠标类型进行对应处理操作
void OpenGlRenderWin::mouseMoveEvent(QMouseEvent *event)
{
    QPoint diff = event->pos() - mousePressPosition;
    if(this->m_MouseFlag == Qt::LeftButton)
    {
        //按下鼠标左键并移动控制被观察物体绕x轴和y轴进行旋转
        this->m_xRot = setRotation(4 * diff.x());
        this->m_yRot = setRotation(4 * diff.y());
    }else if(this->m_MouseFlag == Qt::RightButton)
    {
        //按下鼠标右键并移动控制被观察物体绕x轴和z轴进行旋转
        this->m_xRot = setRotation(4 * diff.x());
        this->m_zRot = setRotation(4 * diff.y());
    }else if(this->m_MouseFlag == Qt::MidButton)
    {
        //按下鼠标中键（即滚轮）并移动实现被观察物体的拖拽平移
        if(!this->m_MousePressFlag)
            return;
        //以下计算是将在界面内移动鼠标的距离投影到被观察物体的xoy平面内，得到物体实际应该移动的距离
        qreal w_h_ratio = (qreal)(this->width()) / (qreal)(this->height());
        qreal cube_view_height = 2 * Camera.zoom * Camera.distance *qTan(qDegreesToRadians(Camera.fovy/2));
        qreal cube_view_width = w_h_ratio * cube_view_height;

        this->m_xTrans = cube_view_width / qreal(this->width()) * qreal(diff.x());
        this->m_yTrans = cube_view_height / qreal(this->height()) * qreal(diff.y());
    }
    update();
}
//鼠标释放后，记录当前的旋转或平移矩阵
void OpenGlRenderWin::mouseReleaseEvent(QMouseEvent *event)
{
    if((event->button() & Qt::LeftButton) || (event->button() & Qt::RightButton))
    {
        this->m_MousePressFlag = false;
        QMatrix4x4 m;
        //此处注意，因为欧拉旋转的特性，物体绕三个轴旋转的顺序不同，最终旋转后得到的物体角度是不相同的，所以，每次旋转要保证轴的顺序一致
        m.rotate(qreal(this->m_zRot)/16.0f, 0.0f, 0.0f, 1.0f);
        m.rotate(qreal(this->m_yRot)/16.0f, 0.0f, 1.0f, 0.0f);
        m.rotate(qreal(this->m_xRot)/16.0f, 1.0f, 0.0f, 0.0f);
        this->m_rotation = m * this->m_rotation;
        this->m_xRot = 0;
        this->m_yRot = 0;
        this->m_zRot = 0;
    }else if(event->button() & Qt::MidButton)
    {
        this->m_MousePressFlag = false;
        QMatrix4x4 m;
        m.translate(this->m_xTrans, -1.0*this->m_yTrans, 0);
        this->m_translation = m*this->m_translation;
        this->m_xTrans = 0;
        this->m_yTrans = 0;
    }
}
//编译着色器并连接绑定
void OpenGlRenderWin::initShaders()
{
    const char *vshader_code =
            "#version 330 core                        \n"
            "in vec4 vPosition;                       \n"
            "in vec3 aColor;                          \n"
            "in vec3 aNormal;                         \n"
            "out vec3 vColor;                         \n"
            "out vec3 vNormal;                        \n"
            "out vec3 FragPos;                        \n"
            "uniform mat4 mvp_matrix;                 \n"
            "void main()                              \n"
            "{                                        \n"
            "    gl_Position = mvp_matrix * vPosition;    \n"
            "    FragPos = vec3(vPosition);                 \n"
            "    vNormal = mat3(transpose(inverse(mvp_matrix))) * aNormal;\n"
            "    vColor = aColor;                     \n"
            "}                                        \n";

    const char *fshader_code =
            "#version 330 core                        \n"
            "struct Material {                        \n"
            "float ambient;                           \n"
            "float diffuse;                           \n"
            "float specular;                          \n"
            "float shininess;                         \n"
            "};                                       \n"
            "struct Light {                           \n"
            "    vec3 position;                       \n"
            "    vec3 color;                          \n"
            "};                                       \n"
            "in vec3 vColor;                          \n"
            "in vec3 vNormal;                         \n"
            "in vec3 FragPos;                         \n"
            "uniform vec3 viewPos;                    \n"
            "uniform Material material;               \n"
            "uniform Light light1;                     \n"
            "vec3 CalcLightResult(Light light){                                                          \n"
            "vec3 norm = normalize(vNormal);                                                            \n"
            "vec3 lightDir = normalize(light.position - FragPos);                                       \n"
            "float diff = max(dot(norm, lightDir), 0.0);                                                \n"
            "vec3 diffuse = light.color * diff;                                                         \n"
            "vec3 viewDir = normalize(viewPos - FragPos);                                               \n"
            "vec3 reflectDir = reflect(-lightDir, norm);                                                \n"
            "float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);                  \n"
            "vec3 specular = material.specular * spec * light.color;                                    \n"
            "// final                                                                                   \n"
            "return (material.ambient + diffuse + specular) * vColor;}                                           \n"
            "void main()                                                                                \n"
            "{                                                                                          \n"
            "vec3 light1Result = CalcLightResult(light1);                                               \n"
            "    gl_FragColor = vec4(light1Result,1.0f);                                                      \n"
            "}                                                                                          \n";

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    if(!vshader->compileSourceCode(vshader_code))
    {
        qDebug()<<"vshader code error.";
    }

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    if(!fshader->compileSourceCode(fshader_code))
    {
        qDebug()<<"fshader code error.";
    }

    program = new QOpenGLShaderProgram();
    program->addShader(vshader);
    program->addShader(fshader);

    program->link();
    program->bind();
}

void OpenGlRenderWin::initTextures()
{
}

int OpenGlRenderWin::setRotation(int angle)
{
    normalizeAngle(angle);
    return angle;
}

void OpenGlRenderWin::normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void OpenGlRenderWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //此处注意，一定是先将物体进行旋转，再进行平移缩放等其他变换
    //三维空间中的所有变换都是通过矩阵的左乘来实现的（这部分不知道的可单独查资料学习一下哈），因为旋转矩阵是第一个对物体空间坐标进行左乘处理的！
    QMatrix4x4 rotation;
    rotation.rotate(qreal(this->m_zRot)/16.0f, 0.0f, 0.0f, 1.0f);
    rotation.rotate(qreal(this->m_yRot)/16.0f, 0.0f, 1.0f, 0.0f);
    rotation.rotate(qreal(this->m_xRot)/16.0f, 1.0f, 0.0f, 0.0f);
    //计算得到当前旋转矩阵
    rotation = rotation * this->m_rotation;

    QMatrix4x4 m1,m2;
    //得到当前观察者矩阵
    m1.lookAt(Camera.eye, Camera.center, Camera.up);
    m1 = m1 * rotation;
    //得到当前平移矩阵
    m2.translate(this->m_xTrans, -1.0*this->m_yTrans, 0);
    m2 = m2 * this->m_translation;
    program->setUniformValue("mvp_matrix", projection * m2 * m1);
    // add by light
    program->setUniformValue("viewPos", Camera.eye);
    // 设定灯光位置与颜色
    program->setUniformValue("light1.position", QVector3D({10,10,0}));
    program->setUniformValue("light1.color", QVector3D({255.0,255.0,255.0}));
    CommonNS::Material _material = {0.1, 0.9, 0.5, 16};
    // 设定材质
    program->setUniformValue("material.ambient", _material.ambient);
    program->setUniformValue("material.diffuse", _material.diffuse);
    program->setUniformValue("material.specular", _material.specular);
    program->setUniformValue("material.shininess", _material.shininess);
    this->cubeGeometry->drawCubeGeometry(program);
}

} // OpenGlRender
