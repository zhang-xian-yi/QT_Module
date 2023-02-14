#include "ScaleGizmo.h"
#include "Model/ModelLoader.h"

ScaleGizmo::ScaleGizmo(QObject* parent): AbstractGizmo(0) {
    setObjectName("Scaling Gizmo");
    m_markers.resize(3);

    int tmp_log_level = log_level;
    log_level = LOG_LEVEL_WARNING;

    ModelLoader loader;
    m_markers[0] = loader.loadMeshFromFile(":/resources/shapes/ScaleX.obj");
    m_markers[1] = loader.loadMeshFromFile(":/resources/shapes/ScaleY.obj");
    m_markers[2] = loader.loadMeshFromFile(":/resources/shapes/ScaleZ.obj");

    m_markers[0]->material()->setColor(QVector3D(1, 0, 0));
    m_markers[1]->material()->setColor(QVector3D(0, 1, 0));
    m_markers[2]->material()->setColor(QVector3D(0, 0, 1));

    for (int i = 0; i < m_markers.size(); i++) {
        m_markers[i]->setObjectName("Gizmo Marker");
        m_markers[i]->setParent(this);
    }

    log_level = tmp_log_level;

    setParent(parent);
}

ScaleGizmo::~ScaleGizmo() {}

void ScaleGizmo::translate(QVector3D) {
    if (log_level >= LOG_LEVEL_WARNING)
        dout << "Translating a SCALING ONLY gizmo is not allowed.";
}

void ScaleGizmo::rotate(QQuaternion) {
    if (log_level >= LOG_LEVEL_WARNING)
        dout << "Rotating a SCALING ONLY gizmo is not allowed.";
}

void ScaleGizmo::rotate(QVector3D) {
    if (log_level >= LOG_LEVEL_WARNING)
        dout << "Rotating a SCALING ONLY gizmo is not allowed.";
}

void ScaleGizmo::scale(QVector3D scaling) {
    if (m_host)
        m_host->scale(scaling);
}

QVector3D ScaleGizmo::position() const {
    if (m_host)
        return m_host->position();
    else
        return QVector3D(0, 0, 0);
}

QVector3D ScaleGizmo::rotation() const {
    if (m_host)
        return m_host->rotation();
    else
        return QVector3D(0, 0, 0);
}

QVector3D ScaleGizmo::scaling() const {
    if (m_host)
        return m_host->scaling();
    else
        return QVector3D(0, 0, 0);
}

QMatrix4x4 ScaleGizmo::globalSpaceMatrix() const {
    QMatrix4x4 model = localModelMatrix();

    if (m_host) {
        AbstractEntity* parent = qobject_cast<AbstractEntity*>(m_host->parent());
        while (parent) {
            model = parent->globalModelMatrix() * model;
            parent = qobject_cast<AbstractEntity*>(parent->parent());
        }
    }

    return model;
}

QMatrix4x4 ScaleGizmo::globalModelMatrix() const {
    QMatrix4x4 model;
    model.translate(globalSpaceMatrix() * QVector3D(0, 0, 0));

    if (m_host) {
        QQuaternion globalRotation = QQuaternion::fromEulerAngles(rotation());
        AbstractEntity* parent = qobject_cast<AbstractEntity*>(m_host->parent());
        while (parent) {
            globalRotation = QQuaternion::fromEulerAngles(parent->rotation()) * globalRotation;
            parent = qobject_cast<AbstractEntity*>(parent->parent());
        }
        model.rotate(globalRotation);
    }

    return model;
}

void ScaleGizmo::drag(QPoint from, QPoint to, int scnWidth, int scnHeight, QMatrix4x4 proj, QMatrix4x4 view) {
    if (m_host == 0) return;
    Line l1 = screenPosToWorldRay(QVector2D(from), QVector2D(scnWidth, scnHeight), proj, view);
    Line l2 = screenPosToWorldRay(QVector2D(to), QVector2D(scnWidth, scnHeight), proj, view);
    QMatrix4x4 invModelMat = globalSpaceMatrix().inverted();
    l1 = invModelMat * l1;
    l2 = invModelMat * l2;
    if (m_axis == X) {
        Line x = { QVector3D(0, 0, 0), QVector3D(1, 0, 0) };
        QVector3D p1 = getClosestPointOfLines(x, l1);
        QVector3D p2 = getClosestPointOfLines(x, l2);
        scale(QVector3D(p2.x() / p1.x(), 1.0f, 1.0f));
    } else if (m_axis == Y) {
        Line y = { QVector3D(0, 0, 0), QVector3D(0, 1, 0) };
        QVector3D p1 = getClosestPointOfLines(y, l1);
        QVector3D p2 = getClosestPointOfLines(y, l2);
        scale(QVector3D(1.0f, p2.y() / p1.y(), 1.0f));
    } else if (m_axis == Z) {
        Line z = { QVector3D(0, 0, 0), QVector3D(0, 0, 1) };
        QVector3D p1 = getClosestPointOfLines(z, l1);
        QVector3D p2 = getClosestPointOfLines(z, l2);
        scale(QVector3D(1.0f, 1.0f, p2.z() / p1.z()));
    }
}

void ScaleGizmo::setPosition(QVector3D) {
    if (log_level >= LOG_LEVEL_WARNING)
        dout << "Setting the position of a SCALING ONLY gizmo is not allowed";
}

void ScaleGizmo::setRotation(QQuaternion) {
    if (log_level >= LOG_LEVEL_WARNING)
        dout << "Setting the rotation of a SCALING ONLY gizmo is not allowed";
}

void ScaleGizmo::setRotation(QVector3D) {
    if (log_level >= LOG_LEVEL_WARNING)
        dout << "Setting the rotation of a SCALING ONLY gizmo is not allowed";
}

void ScaleGizmo::setScaling(QVector3D scaling) {
    if (m_host)
        m_host->setScaling(scaling);
}
