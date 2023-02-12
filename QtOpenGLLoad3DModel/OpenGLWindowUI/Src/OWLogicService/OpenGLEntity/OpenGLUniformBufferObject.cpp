#include "OpenGLUniformBufferObject.h"

OpenGLUniformBufferObject::OpenGLUniformBufferObject() {
    m_id = 0;
}

OpenGLUniformBufferObject::~OpenGLUniformBufferObject() {
    if (m_id) destroy();
}

GLuint OpenGLUniformBufferObject::bufferId() const {
    return m_id;
}

bool OpenGLUniformBufferObject::create() {
    if (m_id) destroy();
    glGenBuffers(1, &m_id);
    return m_id > 0;
}

void OpenGLUniformBufferObject::allocate(int indx, const void * data, int count) {
    if (m_id == 0) return;
    glBufferData(GL_UNIFORM_BUFFER, count, data, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, indx, m_id, 0, count);
}

void OpenGLUniformBufferObject::destroy() {
    if (m_id) {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

void OpenGLUniformBufferObject::bind() {
    if (m_id)
        glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void OpenGLUniformBufferObject::write(int offset, const void * data, int count) {
    if (m_id)
        glBufferSubData(GL_UNIFORM_BUFFER, offset, count, data);
}

void OpenGLUniformBufferObject::release() {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLUniformBufferObject::bindUniformBlock(QOpenGLShaderProgram* shader) {

    GLuint indx = glGetUniformBlockIndex(shader->programId(), "CameraInfo");
    glUniformBlockBinding(shader->programId(), indx, CAMERA_INFO_BINDING_POINT);
    indx = glGetUniformBlockIndex(shader->programId(), "ModelInfo");
    glUniformBlockBinding(shader->programId(), indx, MODEL_INFO_BINDING_POINT);
    indx = glGetUniformBlockIndex(shader->programId(), "MaterialInfo");
    glUniformBlockBinding(shader->programId(), indx, MATERIAL_INFO_BINDING_POINT);
    indx = glGetUniformBlockIndex(shader->programId(), "LightInfo");
    glUniformBlockBinding(shader->programId(), indx, LIGHT_INFO_BINDING_POINT);
}
