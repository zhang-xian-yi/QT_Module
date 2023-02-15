#pragma once

#include "Scene.h"

class SceneLoader {
public:
    SceneLoader();

    QSharedPointer<Scene> loadFromFile(QString filePath);

    bool hasErrorLog();
    QString errorLog();

private:
    QSharedPointer<Camera> loadCamera(QDataStream& in);
    QSharedPointer<Gridline> loadGridline(QDataStream& in);
    QSharedPointer<AmbientLight> loadAmbientLight(QDataStream& in);
    QSharedPointer<DirectionalLight> loadDirectionalLight(QDataStream& in);
    QSharedPointer<PointLight> loadPointLight(QDataStream& in);
    QSharedPointer<SpotLight> loadSpotLight(QDataStream& in);
    QSharedPointer<Model> loadModel(QDataStream& in);
    QSharedPointer<Mesh> loadMesh(QDataStream& in);
    QSharedPointer<Material> loadMaterial(QDataStream& in);
    QSharedPointer<Texture> loadTexture(QDataStream& in);

    QVector<QSharedPointer<Texture>> m_textures;
    QString m_log;
};
