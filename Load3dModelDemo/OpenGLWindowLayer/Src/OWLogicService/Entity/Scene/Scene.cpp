#include "Scene.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 引入 dout 引入
Scene::Scene(): QObject(0), m_gizmo(nullptr), m_camera(nullptr) {
    setObjectName("Untitled Scene");
    m_gizmo = QSharedPointer<TransformGizmo>(new TransformGizmo(this));
    m_camera = QSharedPointer<Camera>(new Camera(this));
    m_gridlineNameCounter = 1;
    m_ambientLightNameCounter = 1;
    m_directionalLightNameCounter = 1;
    m_pointLightNameCounter = 1;
    m_spotLightNameCounter = 1;
}

// Add & remove members

Scene::Scene(const Scene & scene): QObject(0) {
    setObjectName(scene.objectName());

    m_gizmo = QSharedPointer<TransformGizmo>(new TransformGizmo(this));
    m_camera = QSharedPointer<Camera>(new Camera(*scene.m_camera));
    m_gridlineNameCounter = scene.m_gridlineNameCounter;
    m_ambientLightNameCounter = scene.m_ambientLightNameCounter;
    m_directionalLightNameCounter = scene.m_directionalLightNameCounter;
    m_pointLightNameCounter = scene.m_pointLightNameCounter;
    m_spotLightNameCounter = scene.m_spotLightNameCounter;

    for (int i = 0; i < scene.m_gridlines.size(); i++)
        addGridline(QSharedPointer<Gridline>(new Gridline(*scene.m_gridlines[i])));
    for (int i = 0; i < scene.m_ambientLights.size(); i++)
        addAmbientLight(QSharedPointer<AmbientLight>(new AmbientLight(*scene.m_ambientLights[i])));
    for (int i = 0; i < scene.m_directionalLights.size(); i++)
        addDirectionalLight(QSharedPointer<DirectionalLight>(new DirectionalLight(*scene.m_directionalLights[i])));
    for (int i = 0; i < scene.m_pointLights.size(); i++)
        addPointLight(QSharedPointer<PointLight>(new PointLight(*scene.m_pointLights[i])));
    for (int i = 0; i < scene.m_spotLights.size(); i++)
        addSpotLight(QSharedPointer<SpotLight>(new SpotLight(*scene.m_spotLights[i])));
    for (int i = 0; i < scene.m_models.size(); i++)
        addModel(QSharedPointer<Model>(new Model(*scene.m_models[i])));
}

Scene::~Scene() {

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Scene" << this->objectName() << "is destroyed";
}

bool Scene::setCamera(QSharedPointer<Camera> camera) {
    if (m_camera == camera) return false;
    
    // 智能指针自动释放
    if (m_camera) {
        m_camera.clear();
    }
    

    if (camera) {
        m_camera = camera;
        //m_camera->setParent(this);
        if (logLV >= LOG_LEVEL_INFO)
            dout << "Camera" << camera->objectName() << "is assigned to scene" << this->objectName();
    }

    cameraChanged(m_camera);
    return true;
}

bool Scene::addGridline(QSharedPointer<Gridline> gridline) {
    if (!gridline || m_gridlines.contains(gridline))
        return false;

    m_gridlines.push_back(gridline);
    //gridline->setParent(this);
    gridline->setObjectName("Gridline" + QString::number(m_gridlineNameCounter++));
    gridlineAdded(gridline);

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Gridline" << gridline->objectName() << "is added to scene" << this->objectName();

    return true;
}

bool Scene::addLight(AbstractLight * l) {
    if (SpotLight* light = qobject_cast<SpotLight*>(l))
        return addSpotLight(QSharedPointer<SpotLight>(light));
    else if (AmbientLight* light = qobject_cast<AmbientLight*>(l))
        return addAmbientLight(QSharedPointer<AmbientLight>(light));
    else if (DirectionalLight* light = qobject_cast<DirectionalLight*>(l))
        return addDirectionalLight(QSharedPointer<DirectionalLight>(light));
    else if (PointLight* light = qobject_cast<PointLight*>(l))
        return addPointLight(QSharedPointer<PointLight>(light));
    return false;
}

bool Scene::addAmbientLight(QSharedPointer<AmbientLight> light) {
    if (!light || m_ambientLights.contains(light))
        return false;
    if (m_ambientLights.size() >= 8) {
        if (logLV >= LOG_LEVEL_WARNING)
            dout << "The amount of ambient lights has reached the upper limit of 8.";
        return false;
    }

    m_ambientLights.push_back(light);
    //light->setParent(this);
    light->setObjectName("AmbientLight" + QString::number(m_ambientLightNameCounter++));
    lightAdded(light.get());

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Ambient light" << light->objectName() << "is added to scene" << this->objectName();

    return true;
}

bool Scene::addDirectionalLight(QSharedPointer<DirectionalLight> light) {
    if (!light || m_directionalLights.contains(light))
        return false;
    if (m_directionalLights.size() >= 8) {
        if (logLV >= LOG_LEVEL_WARNING)
            dout << "The amount of directional lights has reached the upper limit of 8.";
        return false;
    }

    m_directionalLights.push_back(light);
    //light->setParent(this);
    light->setObjectName("DirectionalLight" + QString::number(m_directionalLightNameCounter++));
    lightAdded(light.get());

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Directional light" << light->objectName() << "is added to scene" << this->objectName();

    return true;
}

bool Scene::addPointLight(QSharedPointer<PointLight> light) {
    if (!light || m_pointLights.contains(light))
        return false;
    if (m_pointLights.size() >= 8) {
        if (logLV >= LOG_LEVEL_WARNING)
            dout << "The amount of point lights has reached the upper limit of 8.";
        return false;
    }

    m_pointLights.push_back(light);
    //light->setParent(this);
    light->setObjectName("PointLight" + QString::number(m_pointLightNameCounter++));
    lightAdded(light.get());

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Point light" << light->objectName() << "is added to scene" << this->objectName();

    return true;
}

bool Scene::addSpotLight(QSharedPointer<SpotLight> light) {
    if (!light || m_spotLights.contains(light))
        return false;
    if (m_spotLights.size() >= 8) {
        if (logLV >= LOG_LEVEL_WARNING)
            dout << "The amount of spotlights has reached the upper limit of 8.";
        return false;
    }

    m_spotLights.push_back(light);
    //light->setParent(this);
    light->setObjectName("SpotLight" + QString::number(m_spotLightNameCounter++));
    lightAdded(light.get());

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Spot light" << light->objectName() << "is added to scene" << this->objectName();

    return true;
}

bool Scene::addModel(QSharedPointer<Model> model) {
    if (!model || m_models.contains(model))
        return false;

    m_models.push_back(model);
    //model->setParent(this);
    modelAdded(model);

    if (logLV >= LOG_LEVEL_INFO)
        dout << "Model" << model->objectName() << "is added to scene" << this->objectName();

    return true;
}

bool Scene::removeGridline(QObject * gridline) {
    for (int i = 0; i < m_gridlines.size(); i++)
        if (m_gridlines[i] == gridline) {
            m_gridlines.erase(m_gridlines.begin() + i);
            gridlineRemoved(gridline);
            if (logLV >= LOG_LEVEL_INFO)
                dout << "Gridline" << gridline->objectName() << "is removed from scene" << this->objectName();
            return true;
        }
    return false;
}

bool Scene::removeLight(QObject * light) {
    for (int i = 0; i < m_ambientLights.size(); i++)
        if (m_ambientLights[i] == light) {
            m_ambientLights.erase(m_ambientLights.begin() + i);
            lightRemoved(light);
            if (logLV >= LOG_LEVEL_INFO)
                dout << "Ambient light" << light->objectName() << "is removed from scene" << this->objectName();
            return true;
        }
    for (int i = 0; i < m_directionalLights.size(); i++)
        if (m_directionalLights[i] == light) {
            m_directionalLights.erase(m_directionalLights.begin() + i);
            lightRemoved(light);
            if (logLV >= LOG_LEVEL_INFO)
                dout << "Directional light" << light->objectName() << "is removed from scene" << this->objectName();
            return true;
        }
    for (int i = 0; i < m_pointLights.size(); i++)
        if (m_pointLights[i] == light) {
            m_pointLights.erase(m_pointLights.begin() + i);
            lightRemoved(light);
            if (logLV >= LOG_LEVEL_INFO)
                dout << "Point light" << light->objectName() << "is removed from scene" << this->objectName();
            return true;
        }
    for (int i = 0; i < m_spotLights.size(); i++)
        if (m_spotLights[i] == light) {
            m_spotLights.erase(m_spotLights.begin() + i);
            lightRemoved(light);
            if (logLV >= LOG_LEVEL_INFO)
                dout << "Spot light" << light->objectName() << "is removed from scene" << this->objectName();
            return true;
        }
    return false;
}

bool Scene::removeModel(QObject * model, bool recursive) {
    for (int i = 0; i < m_models.size(); i++)
        if (m_models[i] == model) {
            m_models.erase(m_models.begin() + i);
            modelRemoved(model);
            if (logLV >= LOG_LEVEL_INFO)
                dout << "Model" << model->objectName() << "is removed from scene" << this->objectName();
            return true;
        }
    if (!recursive) return false;
    for (int i = 0; i < m_models.size(); i++)
        if (m_models[i]->removeChildModel(model, recursive))
            return true;
    return false;
}

// Dump info

void Scene::dumpObjectInfo(int l) {
    qDebug().nospace() << tab(l) << "Scene: " << objectName();
    qDebug("%s%d gridline(s), %d ambient light(s), %d directional light(s), %d point light(s), %d spotlights(s), %d model(s)",
           tab(l),
           m_gridlines.size(),
           m_ambientLights.size(),
           m_directionalLights.size(),
           m_pointLights.size(),
           m_spotLights.size(),
           m_models.size());
}

void Scene::dumpObjectTree(int l) {
    dumpObjectInfo(l);
    m_gizmo->dumpObjectTree(l + 1);
    m_camera->dumpObjectTree(l + 1);
    for (int i = 0; i < m_gridlines.size(); i++)
        m_gridlines[i]->dumpObjectTree(l + 1);
    for (int i = 0; i < m_ambientLights.size(); i++)
        m_ambientLights[i]->dumpObjectTree(l + 1);
    for (int i = 0; i < m_directionalLights.size(); i++)
        m_directionalLights[i]->dumpObjectTree(l + 1);
    for (int i = 0; i < m_pointLights.size(); i++)
        m_pointLights[i]->dumpObjectTree(l + 1);
    for (int i = 0; i < m_spotLights.size(); i++)
        m_spotLights[i]->dumpObjectTree(l + 1);
    for (int i = 0; i < m_models.size(); i++)
        m_models[i]->dumpObjectTree(l + 1);
}

// Get properties

QSharedPointer<TransformGizmo> Scene::transformGizmo() const {
    return m_gizmo;
}

QSharedPointer<Camera> Scene::camera() const {
    return m_camera;
}

const QVector<QSharedPointer<Gridline>>& Scene::gridlines() const {
    return m_gridlines;
}

const QVector<QSharedPointer<AmbientLight>>& Scene::ambientLights() const {
    return m_ambientLights;
}

const QVector<QSharedPointer<DirectionalLight>>& Scene::directionalLights() const {
    return m_directionalLights;
}

const QVector<QSharedPointer<PointLight>>& Scene::pointLights() const {
    return m_pointLights;
}

const QVector<QSharedPointer<SpotLight>>& Scene::spotLights() const {
    return m_spotLights;
}

const QVector<QSharedPointer<Model>>& Scene::models() const {
    return m_models;
}

void Scene::childEvent(QChildEvent * e) {
    if (e->added()) {
        if (Camera* camera = qobject_cast<Camera*>(e->child()))
            setCamera(QSharedPointer<Camera>(camera));
        else if (Gridline* gridline = qobject_cast<Gridline*>(e->child()))
            addGridline(QSharedPointer<Gridline>(gridline));
        else if (AbstractLight* light = qobject_cast<AbstractLight*>(e->child()))
            addLight(light);
        else if (Model* model = qobject_cast<Model*>(e->child()))
            addModel(QSharedPointer<Model>(model));
    } else if (e->removed()) {
        if (m_camera == e->child()) {
            m_camera = 0;
            if (logLV >= LOG_LEVEL_WARNING)
                dout << "Warning: Camera is removed from scene" << this->objectName();
            cameraChanged(0);
            return;
        }
        if (removeGridline(e->child())) return;
        if (removeLight(e->child())) return;
        if (removeModel(e->child(), false)) return;
    }
}
