#pragma once

#include "Scene.h"

class SceneSaver {
public:
    SceneSaver(QSharedPointer<Scene> scene);

    bool saveToFile(QString filePath);

    bool hasErrorLog();
    QString errorLog();

private:
    void getAllTextures(QSharedPointer<Model> model);

    void saveCamera(QSharedPointer<Camera> camera, QDataStream& out);
    void saveGridline(QSharedPointer<Gridline> gridline, QDataStream& out);
    void saveAmbientLight(QSharedPointer<AmbientLight> light, QDataStream& out);
    void saveDirectionalLight(QSharedPointer<DirectionalLight> light, QDataStream& out);
    void savePointLight(QSharedPointer<PointLight> light, QDataStream& out);
    void saveSpotLight(QSharedPointer<SpotLight> light, QDataStream& out);
    void saveModel(QSharedPointer<Model> model, QDataStream& out);
    void saveMesh(QSharedPointer<Mesh> mesh, QDataStream& out);
    void saveMaterial(QSharedPointer<Material> material, QDataStream& out);
    void saveTexture(QSharedPointer<Texture> texture, QDataStream& out);

    QSharedPointer<Scene> m_scene;
    QVector<QSharedPointer<Texture>> m_textures;
    QString m_log;
};
