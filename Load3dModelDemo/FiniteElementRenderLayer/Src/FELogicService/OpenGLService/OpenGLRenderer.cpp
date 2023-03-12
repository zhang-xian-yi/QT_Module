#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer():
    m_pScene(nullptr)
{
    GetMVPMat4 = nullptr;
    Get3DPos = nullptr;
}

void OpenGLRenderer::InitEnv()
{
    m_pScene = QSharedPointer<FEScence>(new FEScence());
    m_pScene->CreateDefaultScence();
    initShaders();//初始化着色器
}

void OpenGLRenderer::Draw()
{
    if(m_pScene == nullptr)
    {
        //第一次渲染窗口 由于文件未加载--需要判空
        //渲染对象不存在则返回 直接返回
        return;
    }

    m_pShaderProgram->setUniformValue("mvp_matrix", this->GetMVPMat4());
    // add by light
    m_pShaderProgram->setUniformValue("viewPos", this->Get3DPos());
    // 设定灯光位置与颜色
    m_pShaderProgram->setUniformValue("light1.position",m_pScene->m_pLightSrc->LPostion);
    m_pShaderProgram->setUniformValue("light1.color", m_pScene->m_pLightSrc->LColor);

    // 设定材质
    m_pShaderProgram->setUniformValue("material.ambient", m_pScene->m_pMaterial->ambient);
    m_pShaderProgram->setUniformValue("material.diffuse", m_pScene->m_pMaterial->diffuse);
    m_pShaderProgram->setUniformValue("material.specular",  m_pScene->m_pMaterial->specular);
    m_pShaderProgram->setUniformValue("material.shininess", m_pScene->m_pMaterial->shininess);

    m_pScene->Draw(m_pShaderProgram);
}


void OpenGLRenderer::SetRendererDataSlot(QSharedPointer<FEModel> pModel)
{
    m_pScene->m_modelVect.append(pModel);
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
