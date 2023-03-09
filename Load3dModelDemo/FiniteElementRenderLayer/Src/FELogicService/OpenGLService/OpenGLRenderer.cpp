#include "OpenGLRenderer.h"

#include "Src/FELogicService/OpenGLEntity/Material.h"//材质

OpenGLRenderer::OpenGLRenderer()
{
    GetMVPMat4 = nullptr;
    Get3DPos = nullptr;
}

void OpenGLRenderer::InitEnv()
{
    initShaders();//初始化着色器

    m_pDrawEleS = QSharedPointer<CubeGeometry>(new CubeGeometry());
}

void OpenGLRenderer::Draw()
{
    m_pShaderProgram->setUniformValue("mvp_matrix", this->GetMVPMat4());
    // add by light
    m_pShaderProgram->setUniformValue("viewPos", this->Get3DPos());
    // 设定灯光位置与颜色
    m_pShaderProgram->setUniformValue("light1.position", QVector3D({10,10,0}));
    m_pShaderProgram->setUniformValue("light1.color", QVector3D({255.0,255.0,255.0}));

    Material material(0.1f,0.9f,0.5f,16);
    // 设定材质
    m_pShaderProgram->setUniformValue("material.ambient", material.ambient);
    m_pShaderProgram->setUniformValue("material.diffuse", material.diffuse);
    m_pShaderProgram->setUniformValue("material.specular",  material.specular);
    m_pShaderProgram->setUniformValue("material.shininess", material.shininess);

    m_pDrawEleS->drawCubeGeometry(m_pShaderProgram);
}


void OpenGLRenderer::SetRendererData(QSharedPointer<FEModel> pModel)
{
    m_pDrawEleS->SetRenderData(pModel->verticesVect,pModel->meshVect);
}

//编译着色器并连接绑定
void OpenGLRenderer::initShaders()
{
    m_pShaderProgram = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram());
    m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Res/shaders/basic.vert");
    m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Res/shaders/basic.frag");
    if(!m_pShaderProgram->link())
    {
        qDebug()<<"shader linkes error";
    }

    if(!m_pShaderProgram->bind())
    {
        qDebug()<<"shader bind error";
    }
}

void OpenGLRenderer::SetGetCallBack(GetMat4Callback Mat4FCB)
{
    this->GetMVPMat4 = Mat4FCB;
}

void OpenGLRenderer::SetGetCallBack(GetVec3DCallback vec3DFCB)
{
    this->Get3DPos = vec3DFCB;
}
