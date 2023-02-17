#include "OpenGLScene.h"

struct ShaderAxisInfo { // struct size: 64
    //                         // base align  // aligned offset
    float hostModelMat[16];    // 64          // 0
} shaderAxisInfo;

struct ShaderCameraInfo { // struct size: 144
    //                         // base align  // aligned offset
    float projMat[16];         // 64          // 0
    float viewMat[16];         // 64          // 64
    QVector4D cameraPos;       // 16          // 128
} shaderCameraInfo;

struct ShaderAmbientLight { // struct size: 16
    //                         // base align  // aligned offset
    QVector4D color;           // 16          // 0
};

struct ShaderDirectionalLight { // struct size: 32
    //                         // base align  // aligned offset
    QVector4D color;           // 16          // 0
    QVector4D direction;       // 16          // 16
};

struct ShaderPointLight { // struct size: 48
    //                           // base align  // aligned offset
    QVector4D color;             // 16          // 0
    QVector4D pos;               // 16          // 16
    QVector4D attenuation;       // 16          // 32
};

struct ShaderSpotLight { // struct size: 80
    //                           // base align  // aligned offset
    QVector4D color;             // 16          // 0
    QVector4D pos;               // 16          // 16
    QVector4D direction;         // 16          // 32
    QVector4D attenuation;       // 16          // 48
    QVector4D cutOff;            // 16          // 64
};

struct ShaderlightInfo { // struct size: 1424
    //                                          // base align  // aligned offset
    int ambientLightNum;                        // 4           // 0
    int directionalLightNum;                    // 4           // 4
    int pointLightNum;                          // 4           // 8
    int spotLightNum;                           // 4           // 12
    ShaderAmbientLight ambientLight[8];         // 16          // 16
    ShaderDirectionalLight directionalLight[8]; // 32          // 144
    ShaderPointLight pointLight[8];             // 48          // 400
    ShaderSpotLight spotLight[8];               // 80          // 784
};

static ShaderlightInfo shaderlightInfo;
QSharedPointer<OpenGLUniformBufferObject> OpenGLScene::m_cameraInfo = 0;
QSharedPointer<OpenGLUniformBufferObject> OpenGLScene::m_lightInfo = 0;
OpenGLScene::OpenGLScene(QSharedPointer<Scene> scene) {
    m_host = scene;

    this->gizmoAdded(m_host->transformGizmo());
    for (int i = 0; i < m_host->gridlines().size(); i++)
        this->gridlineAdded(m_host->gridlines()[i]);
    for (int i = 0; i < m_host->pointLights().size(); i++)
        this->lightAdded(m_host->pointLights()[i]);
    for (int i = 0; i < m_host->spotLights().size(); i++)
        this->lightAdded(m_host->spotLights()[i]);
    for (int i = 0; i < m_host->models().size(); i++)
        this->modelAdded(m_host->models()[i]);

    connect(m_host.get(), SIGNAL(gridlineAdded(QSharedPointer<Gridline>)), this, SLOT(gridlineAdded(QSharedPointer<Gridline>)));
    connect(m_host.get(), SIGNAL(lightAdded(QSharedPointer<AbstractLight>)), this, SLOT(lightAdded(QSharedPointer<AbstractLight>)));
    connect(m_host.get(), SIGNAL(modelAdded(QSharedPointer<Model>)), this, SLOT(modelAdded(QSharedPointer<Model>)));
    connect(m_host.get(), SIGNAL(destroyed(QObject*)), this, SLOT(hostDestroyed(QObject*)));//指针销毁时出现的两次释放
}

//
OpenGLScene::~OpenGLScene()
{
    m_gizmoMeshes.clear();
    m_gridlineMeshes.clear();
    m_normalMeshes.clear();
    m_lightMeshes.clear();
}

QSharedPointer<Scene>  OpenGLScene::host() const {
    return m_host;
}

QSharedPointer<OpenGLMesh> OpenGLScene::pick(uint32_t pickingID) {
    if (pickingID >= 1000 && pickingID - 1000 < (uint32_t) m_normalMeshes.size())
        return m_normalMeshes[pickingID - 1000];
    else if (pickingID >= 100 && pickingID - 100 < (uint32_t) m_lightMeshes.size())
        return m_lightMeshes[pickingID - 100];
    else if (pickingID >= 90 && pickingID - 90 < (uint32_t) m_gizmoMeshes.size())
        return m_gizmoMeshes[pickingID - 90];
    return 0;
}

void OpenGLScene::renderAxis() {
    if (m_host->transformGizmo()->alwaysOnTop())
        glClear(GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < m_gizmoMeshes.size(); i++)
        m_gizmoMeshes[i]->render();
}

void OpenGLScene::renderGridlines() {
    for (int i = 0; i < m_gridlineMeshes.size(); i++)
        m_gridlineMeshes[i]->render();
}

void OpenGLScene::renderLights() {
    for (int i = 0; i < m_lightMeshes.size(); i++) {
        m_lightMeshes[i]->setPickingID(100 + i);
        m_lightMeshes[i]->render();
    }
}

void OpenGLScene::renderModels(bool pickingPass) {
    for (int i = 0; i < m_normalMeshes.size(); i++) {
        m_normalMeshes[i]->setPickingID(1000 + i);
        m_normalMeshes[i]->render(pickingPass);
    }
}

void OpenGLScene::commitCameraInfo() {
    if (!m_host->camera()) return;
    memcpy(shaderCameraInfo.projMat, m_host->camera()->projectionMatrix().constData(), 64);
    memcpy(shaderCameraInfo.viewMat, m_host->camera()->viewMatrix().constData(), 64);
    shaderCameraInfo.cameraPos = m_host->camera()->position();

    if (m_cameraInfo == 0) {
        m_cameraInfo = QSharedPointer<OpenGLUniformBufferObject>(new OpenGLUniformBufferObject);
        m_cameraInfo->create();
        m_cameraInfo->bind();
        m_cameraInfo->allocate(CAMERA_INFO_BINDING_POINT, NULL, sizeof(ShaderCameraInfo));
        m_cameraInfo->release();
    }

    m_cameraInfo->bind();
    m_cameraInfo->write(0, &shaderCameraInfo, sizeof(ShaderCameraInfo));
    m_cameraInfo->release();
}

void OpenGLScene::commitLightInfo() {
    int ambientLightNum = 0, directionalLightNum = 0, pointLightNum = 0, spotLightNum = 0;
    for (int i = 0; i < m_host->ambientLights().size(); i++)
        if (m_host->ambientLights()[i]->enabled()) {
            shaderlightInfo.ambientLight[ambientLightNum].color = m_host->ambientLights()[i]->color() * m_host->ambientLights()[i]->intensity();
            ambientLightNum++;
        }
    for (int i = 0; i < m_host->directionalLights().size(); i++)
        if (m_host->directionalLights()[i]->enabled()) {
            shaderlightInfo.directionalLight[directionalLightNum].color = m_host->directionalLights()[i]->color() * m_host->directionalLights()[i]->intensity();
            shaderlightInfo.directionalLight[directionalLightNum].direction = m_host->directionalLights()[i]->direction();
            directionalLightNum++;
        }
    for (int i = 0; i < m_host->pointLights().size(); i++)
        if (m_host->pointLights()[i]->enabled()) {
            shaderlightInfo.pointLight[pointLightNum].color = m_host->pointLights()[i]->color() * m_host->pointLights()[i]->intensity();
            shaderlightInfo.pointLight[pointLightNum].pos = m_host->pointLights()[i]->position();
            shaderlightInfo.pointLight[pointLightNum].attenuation[0] = m_host->pointLights()[i]->enableAttenuation();
            shaderlightInfo.pointLight[pointLightNum].attenuation[1] = m_host->pointLights()[i]->attenuationQuadratic();
            shaderlightInfo.pointLight[pointLightNum].attenuation[2] = m_host->pointLights()[i]->attenuationLinear();
            shaderlightInfo.pointLight[pointLightNum].attenuation[3] = m_host->pointLights()[i]->attenuationConstant();
            pointLightNum++;
        }
    for (int i = 0; i < m_host->spotLights().size(); i++)
        if (m_host->spotLights()[i]->enabled()) {
            shaderlightInfo.spotLight[spotLightNum].color = m_host->spotLights()[i]->color() * m_host->spotLights()[i]->intensity();
            shaderlightInfo.spotLight[spotLightNum].pos = m_host->spotLights()[i]->position();
            shaderlightInfo.spotLight[spotLightNum].direction = m_host->spotLights()[i]->direction();
            shaderlightInfo.spotLight[spotLightNum].attenuation[0] = m_host->spotLights()[i]->enableAttenuation();
            shaderlightInfo.spotLight[spotLightNum].attenuation[1] = m_host->spotLights()[i]->attenuationQuadratic();
            shaderlightInfo.spotLight[spotLightNum].attenuation[2] = m_host->spotLights()[i]->attenuationLinear();
            shaderlightInfo.spotLight[spotLightNum].attenuation[3] = m_host->spotLights()[i]->attenuationConstant();
            shaderlightInfo.spotLight[spotLightNum].cutOff[0] = (float) cos(rad(m_host->spotLights()[i]->innerCutOff()));
            shaderlightInfo.spotLight[spotLightNum].cutOff[1] = (float) cos(rad(m_host->spotLights()[i]->outerCutOff()));
            spotLightNum++;
        }

    shaderlightInfo.ambientLightNum = ambientLightNum;
    shaderlightInfo.directionalLightNum = directionalLightNum;
    shaderlightInfo.pointLightNum = pointLightNum;
    shaderlightInfo.spotLightNum = spotLightNum;

    if (m_lightInfo == 0) {
        m_lightInfo = QSharedPointer<OpenGLUniformBufferObject>(new OpenGLUniformBufferObject);
        m_lightInfo->create();
        m_lightInfo->bind();
        m_lightInfo->allocate(LIGHT_INFO_BINDING_POINT, NULL, sizeof(ShaderlightInfo));
        m_lightInfo->release();
    }
    m_lightInfo->bind();
    m_lightInfo->write(0, &shaderlightInfo, sizeof(ShaderlightInfo));
    m_lightInfo->release();
}

void OpenGLScene::childEvent(QChildEvent * e) {
    if (e->removed()) {
        for (int i = 0; i < m_gridlineMeshes.size(); i++)
            if (m_gridlineMeshes[i] == e->child())
                m_gridlineMeshes.removeAt(i);
        for (int i = 0; i < m_lightMeshes.size(); i++)
            if (m_lightMeshes[i] == e->child())
                m_lightMeshes.removeAt(i);
        for (int i = 0; i < m_normalMeshes.size(); i++)
            if (m_normalMeshes[i] == e->child())
                m_normalMeshes.removeAt(i);
    }
}

void OpenGLScene::gizmoAdded(QSharedPointer<AbstractGizmo> gizmo)
{
    for (int i = 0; i < gizmo->markers().size(); i++)
    {
        auto tmp = QSharedPointer<OpenGLMesh>(new OpenGLMesh(gizmo->markers()[i], this));
        m_gizmoMeshes.push_back(tmp);
        m_gizmoMeshes.back()->setSizeFixed(true);
        m_gizmoMeshes.back()->setPickingID(90 + i);
    }
}

void OpenGLScene::gridlineAdded(QSharedPointer<Gridline> gridline)
{
    auto tmp = QSharedPointer<OpenGLMesh>(new OpenGLMesh(gridline->marker(), this));
    m_gridlineMeshes.push_back(tmp);
}

void OpenGLScene::lightAdded(QSharedPointer<AbstractLight> light) {
    if (light->marker())
    {
        auto tmp = QSharedPointer<OpenGLMesh>(new OpenGLMesh(light->marker(), this));
        m_lightMeshes.push_back(tmp);
    }
}

void OpenGLScene::modelAdded(QSharedPointer<Model> model)
{
    connect(model.get(), SIGNAL(childMeshAdded(QSharedPointer<Mesh>)), this, SLOT(meshAdded(QSharedPointer<Mesh>)));
    for (int i = 0; i < model->childMeshes().size(); i++)
        meshAdded(model->childMeshes()[i]);
    for (int i = 0; i < model->childModels().size(); i++)
        modelAdded(model->childModels()[i]);
}

void OpenGLScene::meshAdded(QSharedPointer<Mesh> mesh)
{
    auto tmp = QSharedPointer<Mesh>(mesh);
    m_normalMeshes.push_back(QSharedPointer<OpenGLMesh>(new OpenGLMesh(tmp, this)));
}

void OpenGLScene::hostDestroyed(QObject *) {
    // Commit suicide
    delete this;
}
