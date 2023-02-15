#pragma once

#include "Model.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

class ModelExporter {
public:
    ModelExporter();
    ~ModelExporter();

    void saveToFile(QSharedPointer<Model> model, QString filePath);
    void saveToFile(QSharedPointer<Mesh> mesh, QString filePath);

    bool hasErrorLog();
    QString errorLog();

private:
    QString m_log;

    QSharedPointer<Model> m_model;
    QSharedPointer<aiScene> m_aiScenePtr;
    QVector<QSharedPointer<aiMesh>> m_tmp_aiMeshes;
    QVector<QSharedPointer<aiMaterial>> m_tmp_aiMaterials;
    QVector<QSharedPointer<Texture> > m_tmp_textures;

    void getAllTextures(QSharedPointer<Model> model);
    aiNode* exportModel(QSharedPointer<Model> model);
    aiMesh* exportMesh(QSharedPointer<Mesh> mesh);
    aiMaterial* exportMaterial(QSharedPointer<Material> material);
};
