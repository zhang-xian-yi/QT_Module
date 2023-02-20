#include "OpenGLUniformBufferObject.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入

OpenGLUniformBufferObject::OpenGLUniformBufferObject() {
    m_id = 0;
}

OpenGLUniformBufferObject::~OpenGLUniformBufferObject() {
    //m_id =0;
    if (m_id) destroy();
}

GLuint OpenGLUniformBufferObject::bufferId() const {
    return m_id;
}

bool OpenGLUniformBufferObject::create() {
    if (m_id) destroy();
    pGlFuncs->glGenBuffers(1, &m_id);
    return m_id > 0;
}

void OpenGLUniformBufferObject::allocate(int indx, const void * data, int count) {
    if (m_id == 0) return;
    if (!pGlFuncs) return;
    pGlFuncs->glBufferData(GL_UNIFORM_BUFFER, count, data, GL_STATIC_DRAW);
    pGlFuncs->glBindBufferRange(GL_UNIFORM_BUFFER, indx, m_id, 0, count);
}

void OpenGLUniformBufferObject::destroy()
{
    if (m_id && pGlFuncs)
    {
        pGlFuncs->glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

void OpenGLUniformBufferObject::bind()
{
    if (m_id && pGlFuncs)
        pGlFuncs->glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void OpenGLUniformBufferObject::write(int offset, const void * data, int count) {
    if (m_id && pGlFuncs)
        pGlFuncs->glBufferSubData(GL_UNIFORM_BUFFER, offset, count, data);
}

void OpenGLUniformBufferObject::release() {
        pGlFuncs->glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLUniformBufferObject::bindUniformBlock(QOpenGLShaderProgram* shader) {
    GLuint indx = pGlFuncs->glGetUniformBlockIndex(shader->programId(), "CameraInfo");
    pGlFuncs->glUniformBlockBinding(shader->programId(), indx, CAMERA_INFO_BINDING_POINT);
    indx = pGlFuncs->glGetUniformBlockIndex(shader->programId(), "ModelInfo");
    pGlFuncs->glUniformBlockBinding(shader->programId(), indx, MODEL_INFO_BINDING_POINT);
    indx = pGlFuncs->glGetUniformBlockIndex(shader->programId(), "MaterialInfo");
    pGlFuncs->glUniformBlockBinding(shader->programId(), indx, MATERIAL_INFO_BINDING_POINT);
    indx = pGlFuncs->glGetUniformBlockIndex(shader->programId(), "LightInfo");
    pGlFuncs->glUniformBlockBinding(shader->programId(), indx, LIGHT_INFO_BINDING_POINT);
}
