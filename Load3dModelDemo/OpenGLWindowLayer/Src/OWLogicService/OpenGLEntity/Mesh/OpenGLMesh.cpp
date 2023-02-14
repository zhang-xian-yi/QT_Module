#include "OpenGLMesh.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
struct ShaderModelInfo {
    float modelMat[16];   // 64          // 0
    float normalMat[16];  // 64          // 64
    int sizeFixed;        // 4           // 128
    int selected;         // 4           // 132
    int highlighted;      // 4           // 136
    uint pickingID;        // 4           // 140
};

static ShaderModelInfo shaderModelInfo;

OpenGLUniformBufferObject *OpenGLMesh::m_modelInfo = 0;

OpenGLMesh::OpenGLMesh(Mesh * mesh, QObject* parent): QObject(0) {
    m_host = mesh;
    m_sizeFixed = false;
    m_pickingID = 0;
    m_vao = 0;
    m_vbo = 0;
    m_ebo = 0;
    if (m_host->material())
        m_openGLMaterial = new OpenGLMaterial(m_host->material());
    else
        m_openGLMaterial = nullptr;

    connect(m_host, SIGNAL(materialChanged(Material*)), this, SLOT(materialChanged(Material*)));
    connect(m_host, SIGNAL(geometryChanged(QVector<Vertex>, QVector<uint32_t>)), this, SLOT(geometryChanged(QVector<Vertex>, QVector<uint32_t>)));
    connect(m_host, SIGNAL(destroyed(QObject*)), this, SLOT(hostDestroyed(QObject*)));

    setParent(parent);
}

OpenGLMesh::~OpenGLMesh() {
    this->destroy();
    //此函数不止虚构会调用，如果将m_openGLMaterial释放也放入destory 那场景中可能会失去颜色纹理信息描述
    //释放此处空间，将不会描述纹理和颜色
    if(m_openGLMaterial)
    {
        delete m_openGLMaterial;
        m_openGLMaterial = nullptr;
    }
}

Mesh * OpenGLMesh::host() const {
    return m_host;
}

void OpenGLMesh::create() {
    this->destroy();

    m_vao = new QOpenGLVertexArrayObject;
    m_vao->create();
    m_vao->bind();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    if (m_host->vertices().size())
        m_vbo->allocate(&m_host->vertices()[0], int(sizeof(Vertex) * m_host->vertices().size()));
    m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ebo->create();
    m_ebo->bind();
    if (m_host->indices().size())
        m_ebo->allocate(&m_host->indices()[0], int(sizeof(uint32_t) * m_host->indices().size()));


    //pGlFuncs 为GLobalData中的全局宏定义， 保存OpenGL的方法函数
    pGlFuncs->glEnableVertexAttribArray(0);
    pGlFuncs->glEnableVertexAttribArray(1);
    pGlFuncs->glEnableVertexAttribArray(2);
    pGlFuncs->glEnableVertexAttribArray(3);
    pGlFuncs->glEnableVertexAttribArray(4);
    pGlFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    pGlFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
    pGlFuncs->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tangent));
    pGlFuncs->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, bitangent));
    pGlFuncs->glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));

    m_vao->release();
}

void OpenGLMesh::commit() {
    QMatrix4x4 modelMat = m_host->globalModelMatrix();

    memcpy(shaderModelInfo.modelMat, modelMat.constData(), 64);
    memcpy(shaderModelInfo.normalMat, QMatrix4x4(modelMat.normalMatrix()).constData(), 64);
    shaderModelInfo.sizeFixed = this->m_sizeFixed;
    shaderModelInfo.selected = m_host->selected();
    shaderModelInfo.highlighted = m_host->highlighted();
    shaderModelInfo.pickingID = this->m_pickingID;

    if (m_modelInfo == 0) {
        m_modelInfo = new OpenGLUniformBufferObject;
        m_modelInfo->create();
        m_modelInfo->bind();
        m_modelInfo->allocate(MODEL_INFO_BINDING_POINT, NULL, sizeof(ShaderModelInfo));
        m_modelInfo->release();
    }
    m_modelInfo->bind();
    m_modelInfo->write(0, &shaderModelInfo, sizeof(ShaderModelInfo));
    m_modelInfo->release();
}

void OpenGLMesh::render(bool pickingPass) {
    if (!m_host->visible()) return;
    if (m_vao == 0 || m_vbo == 0 || m_ebo == 0) create();

    commit();

    if (!pickingPass && m_host->wireFrameMode())
        pGlFuncs->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (m_openGLMaterial)
        m_openGLMaterial->bind();

    m_vao->bind();

    if (m_host->meshType() == Mesh::Triangle)
        pGlFuncs->glDrawElements(GL_TRIANGLES, (GLsizei) m_host->indices().size(), GL_UNSIGNED_INT, 0);
    else if (m_host->meshType() == Mesh::Line)
        pGlFuncs->glDrawElements(GL_LINES, (GLsizei) m_host->indices().size(), GL_UNSIGNED_INT, 0);
    else
        pGlFuncs->glDrawElements(GL_POINTS, (GLsizei) m_host->indices().size(), GL_UNSIGNED_INT, 0);

    m_vao->release();

    if (!pickingPass && m_host->wireFrameMode())
        pGlFuncs->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if (m_openGLMaterial)
        m_openGLMaterial->release();
}

void OpenGLMesh::destroy() {
    if (m_vao)
    {
        delete m_vao;
        m_vao = nullptr;
    }
    if (m_vbo)
    {
         delete m_vbo;
        m_vbo = nullptr;
    }
    if (m_ebo)
    {
        delete m_ebo;
        m_ebo = nullptr;
    }
}

void OpenGLMesh::setSizeFixed(bool sizeFixed) {
    m_sizeFixed = sizeFixed;
}

void OpenGLMesh::setPickingID(uint id) {
    m_pickingID = id;
}

void OpenGLMesh::childEvent(QChildEvent * e) {
    if (e->removed()) {
        if (e->child() == m_openGLMaterial)
            m_openGLMaterial = 0;
    }
}

void OpenGLMesh::materialChanged(Material * material) {
    if (material == 0)
        m_openGLMaterial = 0;
    else
        m_openGLMaterial = new OpenGLMaterial(material);
}

void OpenGLMesh::geometryChanged(const QVector<Vertex>&, const QVector<uint32_t>&) {
    this->create();
}

void OpenGLMesh::hostDestroyed(QObject *) {
    // Commit suicide
    delete this;
}
