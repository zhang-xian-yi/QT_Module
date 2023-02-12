#include "Load3DModelService.h"
#include "Load3DModel/Src/LMLogicService/Entity/Model/ModelLoader.h"
#include "Load3DModel/Src/LMLogicService/Entity/Model/Model.h"
#include "Load3DModel/Src/LMLogicService/Entity/Scene/Scene.h"
#include "Load3DModel/Src/LMLogicService/Entity/GridLine/Gridline.h"
#include "Load3DModel/Src/LMLogicService/Light/DirectionalLight.h"
namespace Load3dModelNS
{
    Load3DModelService::Load3DModelService()
    {
        //初始化场景
        m_host = new Scene();
        m_host->addGridline(new Gridline);//添加网格
        m_host->addDirectionalLight(new DirectionalLight(QVector3D(1, 1, 1), QVector3D(-2, -4, -3)));//添加方向光
    }

    Load3DModelService::~Load3DModelService()
    {
        if(m_host)
        {
            delete m_host;
            m_host = nullptr;
        }
    }

    Scene *Load3DModelService::Load3DModelFromFile(const QString &modelPath)
    {
        ModelLoader loader;
        Model* model = loader.loadModelFromFile(modelPath);

        if (loader.hasErrorLog())
        {
            QString log = loader.errorLog();
            QMessageBox::critical(0, "Error", log);
        }

        if (m_host && model)
        {
            //向场景中添加模型
            m_host->addModel(model);
        }
        return m_host;
    }

}

