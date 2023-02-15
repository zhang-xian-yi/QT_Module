#include "AbstractGizmo.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
AbstractGizmo::AbstractGizmo(QObject* parent): AbstractEntity(nullptr) {
    m_visible = false;
    m_axis = None;
    m_host = nullptr;
    setParent(parent);
    setObjectName("Untitled Gizmo");
}

AbstractGizmo::~AbstractGizmo()
{
    for(auto tmp:m_markers)
    {
        delete tmp;
    }
    m_markers.clear();
}

bool AbstractGizmo::isGizmo() const {
    return true;
}

bool AbstractGizmo::isLight() const {
    return false;
}

bool AbstractGizmo::isMesh() const {
    return false;
}

bool AbstractGizmo::isModel() const {
    return false;
}

AbstractGizmo::TransformAxis AbstractGizmo::transformAxis() const {
    return m_axis;
}

QVector<Mesh*>& AbstractGizmo::markers() {
    return m_markers;
}

void AbstractGizmo::bindTo(AbstractEntity * host) {
    if (m_host == host) return;
    if (m_host) unbind();
    if (host) {
        m_host = host;
        connect(m_host, SIGNAL(destroyed(QObject*)), this, SLOT(hostDestroyed(QObject*)));

        if (logLV >= LOG_LEVEL_INFO)
            dout << this->objectName() << "is bound to" << host->objectName();
    }
}

void AbstractGizmo::unbind() {
    if (m_host) {
        disconnect(m_host, 0, this, 0);
        m_host = 0;
    }
}

void AbstractGizmo::setTransformAxis(void* marker) {
    for (int i = 0; i < m_markers.size(); i++)
        if (m_markers[i] == marker)
            m_axis = static_cast<AbstractGizmo::TransformAxis>(AbstractGizmo::X + i);
}

void AbstractGizmo::setTransformAxis(TransformAxis axis) {
    m_axis = axis;
}

void AbstractGizmo::hostDestroyed(QObject *) {
    unbind();
}
