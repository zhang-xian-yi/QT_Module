#pragma once

#include "TransformGizmo.h"
#include "Camera/Camera.h"
#include "Gridline/Gridline.h"
#include "AmbientLight/AmbientLight.h"
#include "DirectionalLight/DirectionalLight.h"
#include "PointLight/PointLight.h"
#include "SpotLight/SpotLight.h"
#include "Model/Model.h"

class SceneLoader;
class SceneSaver;

class Scene: public QObject {
    Q_OBJECT

public:
    Scene();
    Scene(const Scene& scene);
    ~Scene();

    bool setCamera(QSharedPointer<Camera> camera);
    bool addGridline(QSharedPointer<Gridline> gridline);
    bool addLight(AbstractLight* light);
    bool addAmbientLight(QSharedPointer<AmbientLight> light);
    bool addDirectionalLight(QSharedPointer<DirectionalLight> light);
    bool addPointLight(QSharedPointer<PointLight> light);
    bool addSpotLight(QSharedPointer<SpotLight> light);
    bool addModel(QSharedPointer<Model> model);

    bool removeGridline(QObject* gridline);
    bool removeLight(QObject* light);
    bool removeModel(QObject* model, bool recursive);

    void dumpObjectInfo(int level = 0);
    void dumpObjectTree(int level = 0);

    QSharedPointer<TransformGizmo> transformGizmo() const;
    QSharedPointer<Camera> camera() const;
    const QVector<QSharedPointer<Gridline>>& gridlines() const;
    const QVector<QSharedPointer<AmbientLight>>& ambientLights() const;
    const QVector<QSharedPointer<DirectionalLight>>& directionalLights() const;
    const QVector<QSharedPointer<PointLight>>& pointLights() const;
    const QVector<QSharedPointer<SpotLight>>& spotLights() const;
    const QVector<QSharedPointer<Model>>& models() const;

signals:
    void cameraChanged(QSharedPointer<Camera> camera);
    void gridlineAdded(QSharedPointer<Gridline> gridline);
    void gridlineRemoved(QObject* object);
    void lightAdded(QSharedPointer<AbstractLight> light);
    void lightRemoved(QObject* object);
    void modelAdded(QSharedPointer<Model> model);
    void modelRemoved(QObject* object);

protected:
    void childEvent(QChildEvent *event) override;

private:
    QSharedPointer<TransformGizmo> m_gizmo;
    QSharedPointer<Camera> m_camera;
    QVector<QSharedPointer<Gridline>> m_gridlines;
    QVector<QSharedPointer<AmbientLight>> m_ambientLights;
    QVector<QSharedPointer<DirectionalLight>> m_directionalLights;
    QVector<QSharedPointer<PointLight>> m_pointLights;
    QVector<QSharedPointer<SpotLight>> m_spotLights;
    QVector<QSharedPointer<Model>> m_models;

    int m_gridlineNameCounter;
    int m_ambientLightNameCounter;
    int m_directionalLightNameCounter;
    int m_pointLightNameCounter;
    int m_spotLightNameCounter;

    friend SceneLoader;
    friend SceneSaver;
};
