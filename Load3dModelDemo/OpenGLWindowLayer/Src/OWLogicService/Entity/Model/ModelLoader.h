#pragma once

#include "Texture/TextureLoader.h"
#include "Model/Model.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

class ModelLoader {
public:
    ModelLoader();

    QSharedPointer<Model> loadModelFromFile(QString filePath);
    QSharedPointer<Mesh> loadMeshFromFile(QString filePath);

    static QSharedPointer<Model> loadConeModel();
    static QSharedPointer<Model> loadCubeModel();
    static QSharedPointer<Model> loadCylinderModel();
    static QSharedPointer<Model> loadPlaneModel();
    static QSharedPointer<Model> loadSphereModel();

    bool hasErrorLog();
    QString errorLog();

private:
    QDir m_dir;
    QString m_log;
    TextureLoader textureLoader;

    const aiScene* m_aiScenePtr;

    QSharedPointer<Model> loadModel(const aiNode* aiNodePtr);
    QSharedPointer<Mesh> loadMesh(const aiMesh* aiMeshPtr);
    QSharedPointer<Material> loadMaterial(const aiMaterial* aiMaterialPtr);
};
