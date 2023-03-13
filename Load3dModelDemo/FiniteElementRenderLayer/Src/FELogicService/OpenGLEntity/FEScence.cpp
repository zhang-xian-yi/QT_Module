#include "FEScence.h"

/*****************************************************************************************************************/
/*      FEScence                                                                                                 */
/*****************************************************************************************************************/

FEScence::FEScence()
{

}

void FEScence::CreateDefaultScence()
{
    m_pLightSrc = QSharedPointer<LightSource>(new LightSource());
    m_pMaterial = QSharedPointer<Material>(new Material());
    m_pMaterial->ambient = 0.1f;
    m_pMaterial->diffuse = 0.9f;
    m_pMaterial->specular = 0.5f;
    m_pMaterial->shininess = 16;

}

void FEScence::Draw(QSharedPointer<QOpenGLShaderProgram> program)
{
    foreach (QSharedPointer<FEModel> pModel, m_modelVect)
    {
        pModel->DrawModel(program);
    }
}


/*****************************************************************************************************************/
/*      LightSource                                                                                               */
/*****************************************************************************************************************/
LightSource::LightSource()
{
    this->LPostion = {10,10,0};
    this->LColor = {255,255,255};
}
