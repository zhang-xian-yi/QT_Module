#pragma once

#include "Scene/Scene.h"
#include "Mesh/OpenGLMesh.h"
#include "OpenGLUniformBufferObject.h"

class OpenGLScene: public QObject {
    Q_OBJECT

public:
    OpenGLScene(QSharedPointer<Scene>  scene);
    ~OpenGLScene();

    QSharedPointer<Scene> host() const;

    QSharedPointer<OpenGLMesh> pick(uint32_t pickingID);

    void renderAxis();
    void renderGridlines();
    void renderLights();
    void renderModels(bool pickingPass = false);

    void commitCameraInfo();
    void commitLightInfo();

protected:
    void childEvent(QChildEvent *event) override;

private:
    QSharedPointer<Scene> m_host;
    //这里的容器是负责Scene中的指针，不用手动释放
    QVector<QSharedPointer<OpenGLMesh>> m_gizmoMeshes, m_gridlineMeshes, m_lightMeshes, m_normalMeshes;
    static OpenGLUniformBufferObject *m_cameraInfo, *m_lightInfo;
private slots:
    void gizmoAdded(QSharedPointer<AbstractGizmo> gizmo);
    void gridlineAdded(QSharedPointer<Gridline> gridline);
    void lightAdded(QSharedPointer<AbstractLight> light);
    void modelAdded(QSharedPointer<Model> model);
    void meshAdded(QSharedPointer<Mesh> mesh);
    void hostDestroyed(QObject* host);
};
