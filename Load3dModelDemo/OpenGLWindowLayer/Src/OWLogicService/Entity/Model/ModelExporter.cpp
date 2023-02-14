#include "ModelExporter.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 引入 dout 引入
// Assimp: 3D model loader
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define toAiString(str) (aiString((str).toStdString()))
#define toAiColor(color) (aiColor3D((color)[0], (color)[1], (color)[2]))
#define toAiVector3D(vec) (aiVector3D((vec)[0], (vec)[1], (vec)[2]))

ModelExporter::ModelExporter() {}

ModelExporter::~ModelExporter() {}

void ModelExporter::saveToFile(Model* model, QString filePath) {
    m_model = model;

    m_tmp_aiMeshes.clear();
    m_tmp_aiMaterials.clear();
    m_tmp_textures.clear();
    getAllTextures(m_model);

    m_aiScenePtr = new aiScene;
    m_aiScenePtr->mRootNode = exportModel(m_model);
    m_aiScenePtr->mNumMeshes = m_tmp_aiMeshes.size();
    m_aiScenePtr->mMeshes = new aiMesh*[m_tmp_aiMeshes.size()];
    m_aiScenePtr->mNumMaterials = m_tmp_aiMaterials.size();
    m_aiScenePtr->mMaterials = new aiMaterial*[m_tmp_aiMaterials.size()];

    for (int i = 0; i < m_tmp_aiMeshes.size(); i++)
        m_aiScenePtr->mMeshes[i] = m_tmp_aiMeshes[i];
    for (int i = 0; i < m_tmp_aiMaterials.size(); i++)
        m_aiScenePtr->mMaterials[i] = m_tmp_aiMaterials[i];

    Assimp::Exporter exporter;
    if (AI_SUCCESS != exporter.Export(m_aiScenePtr,
                                      QFileInfo(filePath).suffix().toStdString(),
                                      filePath.toStdString())) {
        if (logLV >= LOG_LEVEL_ERROR)
            dout << exporter.GetErrorString();
        m_log += exporter.GetErrorString();
        return;
    }

    for (int i = 0; i < m_tmp_textures.size(); i++) {
        QString fileName;
        if (m_tmp_textures[i]->textureType() == Texture::Diffuse)
            fileName = "D_" + QString::number((intptr_t) m_tmp_textures[i].data()) + ".png";
        else if (m_tmp_textures[i]->textureType() == Texture::Specular)
            fileName = "S_" + QString::number((intptr_t) m_tmp_textures[i].data()) + ".png";
        else if (m_tmp_textures[i]->textureType() == Texture::Bump)
            fileName = "N_" + QString::number((intptr_t) m_tmp_textures[i].data()) + ".png";
        m_tmp_textures[i]->image().save(QFileInfo(filePath).absoluteDir().absoluteFilePath(fileName));
    }
}

void ModelExporter::saveToFile(Mesh * mesh, QString filePath) {
    m_tmp_aiMeshes.clear();
    m_tmp_aiMaterials.clear();
    m_tmp_textures.clear();

    m_aiScenePtr = new aiScene;

    m_aiScenePtr->mRootNode = new aiNode;
    m_aiScenePtr->mRootNode->mName = toAiString(mesh->objectName());
    m_aiScenePtr->mRootNode->mNumMeshes = 1;
    m_aiScenePtr->mRootNode->mMeshes = new uint32_t[1];
    m_aiScenePtr->mRootNode->mMeshes[0] = 0;
    m_aiScenePtr->mRootNode->mNumChildren = (uint32_t) 0;
    m_aiScenePtr->mRootNode->mChildren = 0;

    m_aiScenePtr->mNumMeshes = 1;
    m_aiScenePtr->mMeshes = new aiMesh*[1];
    m_aiScenePtr->mMeshes[0] = exportMesh(mesh);
    m_aiScenePtr->mNumMaterials = 1;
    m_aiScenePtr->mMaterials = new aiMaterial*[1];
    m_aiScenePtr->mMaterials[0] = exportMaterial(mesh->material());

    Assimp::Exporter exporter;
    if (AI_SUCCESS != exporter.Export(m_aiScenePtr,
                                      QFileInfo(filePath).suffix().toStdString(),
                                      filePath.toStdString())) {
        m_log += exporter.GetErrorString();
        if (logLV >= LOG_LEVEL_ERROR)
            dout << exporter.GetErrorString();
        return;
    }

    if (mesh->material()) {
        if (Texture* texture = mesh->material()->diffuseTexture().data()) {
            QString fileName = "D_" + QString::number((intptr_t) texture) + ".png";
            texture->image().save(QFileInfo(filePath).absoluteDir().absoluteFilePath(fileName));
        }
        if (Texture* texture = mesh->material()->specularTexture().data()) {
            QString fileName = "S_" + QString::number((intptr_t) texture) + ".png";
            texture->image().save(QFileInfo(filePath).absoluteDir().absoluteFilePath(fileName));
        }
        if (Texture* texture = mesh->material()->bumpTexture().data()) {
            QString fileName = "N_" + QString::number((intptr_t) texture) + ".png";
            texture->image().save(QFileInfo(filePath).absoluteDir().absoluteFilePath(fileName));
        }
    }
}

bool ModelExporter::hasErrorLog() {
    return m_log != "";
}

QString ModelExporter::errorLog() {
    QString tmp = m_log;
    m_log = "";
    return tmp;
}

void ModelExporter::getAllTextures(Model * model) {
    for (int i = 0; i < model->childMeshes().size(); i++)
        if (model->childMeshes()[i]->material()) {
            Material * material = model->childMeshes()[i]->material();
            if (material == 0) continue;
            if (!material->diffuseTexture().isNull() && !m_tmp_textures.contains(material->diffuseTexture()))
                m_tmp_textures.push_back(material->diffuseTexture());
            if (!material->specularTexture().isNull() && !m_tmp_textures.contains(material->specularTexture()))
                m_tmp_textures.push_back(material->specularTexture());
            if (!material->bumpTexture().isNull() && !m_tmp_textures.contains(material->bumpTexture()))
                m_tmp_textures.push_back(material->bumpTexture());
        }
    for (int i = 0; i < model->childModels().size(); i++)
        getAllTextures(model->childModels()[i]);
}

aiNode * ModelExporter::exportModel(Model * model) {
    aiNode* aiNodePtr = new aiNode;
    aiNodePtr->mName = toAiString(model->objectName());

    aiNodePtr->mNumMeshes = (uint32_t) model->childMeshes().size();
    aiNodePtr->mMeshes = new uint32_t[aiNodePtr->mNumMeshes];

    for (int i = 0; i < model->childMeshes().size(); i++) {
        aiNodePtr->mMeshes[i] = m_tmp_aiMeshes.size();
        m_tmp_aiMeshes.push_back(exportMesh(model->childMeshes()[i]));
    }

    aiNodePtr->mNumChildren = (uint32_t) model->childModels().size();
    aiNodePtr->mChildren = new aiNode*[aiNodePtr->mNumChildren];

    for (int i = 0; i < model->childModels().size(); i++)
        aiNodePtr->mChildren[i] = exportModel(model->childModels()[i]);

    return aiNodePtr;
}

aiMesh * ModelExporter::exportMesh(Mesh * mesh) {
    aiMesh* aiMeshPtr = new aiMesh;

    aiMeshPtr->mNumVertices = (uint32_t) mesh->vertices().size();
    aiMeshPtr->mVertices = new aiVector3D[aiMeshPtr->mNumVertices];
    aiMeshPtr->mNormals = new aiVector3D[aiMeshPtr->mNumVertices];
    aiMeshPtr->mTextureCoords[0] = new aiVector3D[aiMeshPtr->mNumVertices];

    for (uint32_t i = 0; i < aiMeshPtr->mNumVertices; i++) {
        Vertex vertex = mesh->globalModelMatrix() * mesh->vertices()[i];
        aiMeshPtr->mVertices[i] = toAiVector3D(vertex.position);
        aiMeshPtr->mNormals[i] = toAiVector3D(vertex.normal);
        aiMeshPtr->mTextureCoords[0][i] = toAiVector3D(QVector3D(vertex.texCoords));
    }

    int indicesEachFace = 0;
    if (mesh->meshType() == Mesh::Triangle)
        indicesEachFace = 3;
    else if (mesh->meshType() == Mesh::Line)
        indicesEachFace = 2;
    else
        indicesEachFace = 1;

    aiMeshPtr->mNumFaces = (uint32_t) mesh->indices().size() / indicesEachFace;
    aiMeshPtr->mFaces = new aiFace[aiMeshPtr->mNumFaces];

    for (uint32_t i = 0; i < aiMeshPtr->mNumFaces; i++) {
        aiFace& face = aiMeshPtr->mFaces[i];
        face.mNumIndices = indicesEachFace;
        face.mIndices = new uint32_t[indicesEachFace];
        for (int j = 0; j < indicesEachFace; j++)
            face.mIndices[j] = mesh->indices()[i * indicesEachFace + j];
    }

    aiMeshPtr->mMaterialIndex = m_tmp_aiMaterials.size();
    m_tmp_aiMaterials.push_back(exportMaterial(mesh->material()));
    return aiMeshPtr;
}

aiMaterial * ModelExporter::exportMaterial(Material * material) {
    aiMaterial* aiMaterialPtr = new aiMaterial;
    if (material == 0) return aiMaterialPtr;

    aiString aiName = toAiString(material->objectName());
    aiColor3D ambientColor = toAiColor(material->ambient() * material->color());
    aiColor3D diffuseColor = toAiColor(material->diffuse() * material->color());
    aiColor3D specularColor = toAiColor(material->specular() * material->color());
    float shininess = material->shininess();

    aiMaterialPtr->AddProperty(&aiName, AI_MATKEY_NAME);
    aiMaterialPtr->AddProperty(&ambientColor, 1, AI_MATKEY_COLOR_AMBIENT);
    aiMaterialPtr->AddProperty(&diffuseColor, 1, AI_MATKEY_COLOR_DIFFUSE);
    aiMaterialPtr->AddProperty(&specularColor, 1, AI_MATKEY_COLOR_SPECULAR);
    aiMaterialPtr->AddProperty(&shininess, 1, AI_MATKEY_SHININESS);

    const int uvwIndex = 0;
    if (material->diffuseTexture()) {
        QString filePath = "D_" + QString::number((intptr_t) material->diffuseTexture().data()) + ".png";
        aiString aiFilePath = toAiString(filePath);
        aiMaterialPtr->AddProperty(&aiFilePath, AI_MATKEY_TEXTURE_DIFFUSE(0));
        aiMaterialPtr->AddProperty(&uvwIndex, 1, AI_MATKEY_UVWSRC_DIFFUSE(0));
    }
    if (material->specularTexture()) {
        QString filePath = "S_" + QString::number((intptr_t) material->specularTexture().data()) + ".png";
        aiString aiFilePath = toAiString(filePath);
        aiMaterialPtr->AddProperty(&aiFilePath, AI_MATKEY_TEXTURE_SPECULAR(0));
        aiMaterialPtr->AddProperty(&uvwIndex, 1, AI_MATKEY_UVWSRC_SPECULAR(0));
    }
    if (material->bumpTexture()) {
        QString filePath = "N_" + QString::number((intptr_t) material->bumpTexture().data()) + ".png";
        aiString aiFilePath = toAiString(filePath);
        aiMaterialPtr->AddProperty(&aiFilePath, AI_MATKEY_TEXTURE_HEIGHT(0));
        aiMaterialPtr->AddProperty(&uvwIndex, 1, AI_MATKEY_UVWSRC_HEIGHT(0));
    }

    return aiMaterialPtr;
}
