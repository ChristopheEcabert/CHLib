/**
 *  @file   mesh.cpp
 *  @brief
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#include "chlib/ogl/ogl_mesh.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name OGLMesh
 *  @fn OGLMesh(void)
 *  @brief  Constructor
 */
template<typename T>
OGLMesh<T>::OGLMesh(void) : Mesh<T>(), vao_(0), vbo_{0} {
}

/*
 *  @name ~OGLMesh
 *  @fn ~OGLMesh(void)
 *  @brief  Destructor
 */
template<typename T>
OGLMesh<T>::~OGLMesh(void) {
  // Clear buffer
  if (vbo_[0] != 0) {
    // Ensure VBO is unbind
    glBindVertexArray(vao_);
    glDeleteBuffers(6, &vbo_[0]);
    memset(reinterpret_cast<void*>(&vbo_[0]),
           0,
           sizeof(vbo_) / sizeof(vbo_[0]));
    glBindVertexArray(0);
  }
  // Clear vao
  if (vao_) {
    glDeleteVertexArrays(1, &vao_);
    vao_ = 0;
  }
}
  
/*
 *  @name InitOpenGLContext
 *  @fn int InitOpenGLContext(void)
 *  @brief  Allocate buffer and push data onto OpenGL context
 *  @return -1 if error, 0 otherwise
 */
template<typename T>
int OGLMesh<T>::InitOpenGLContext(void) {
  int err = -1;
  if (!vao_) {
    // Lazy init
    glGenVertexArrays(1, &vao_);
    // Init buffers
    glBindVertexArray(vao_);
    glGenBuffers(sizeof(vbo_)/sizeof(vbo_[0]), &vbo_[0]);
  } else {
    glBindVertexArray(vao_);
  }
  // Init buffers, VERTEX
  GLenum data_t = sizeof(T) == 4 ? GL_FLOAT : GL_DOUBLE;
  if (this->vertex_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[kVertex]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->vertex_.size() * sizeof(Vertex)),
                 reinterpret_cast<GLvoid*>(this->vertex_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(kVertex);
    glVertexAttribPointer(kVertex, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Normal
  if (this->normal_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[kNormal]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->normal_.size() * sizeof(Normal)),
                 reinterpret_cast<GLvoid*>(this->normal_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(kNormal);
    glVertexAttribPointer(kNormal, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Texture coordinate
  if (this->tex_coord_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[kTCoord]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->tex_coord_.size() * sizeof(TCoord)),
                 reinterpret_cast<GLvoid*>(this->tex_coord_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(kTCoord);
    glVertexAttribPointer(kTCoord, 2, data_t, GL_FALSE, 0, NULL);
  }
  // Tangent space
  if (this->tangent_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[kTangent]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->tangent_.size() * sizeof(Tangent)),
                 reinterpret_cast<GLvoid*>(this->tangent_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(kTangent);
    glVertexAttribPointer(kTCoord, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Vertex color
  if (this->vertex_color_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[kColor]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->vertex_color_.size() * sizeof(Color)),
                 reinterpret_cast<GLvoid*>(this->vertex_color_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(kColor);
    glVertexAttribPointer(kColor, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Triangle
  if (this->tri_.size() > 0) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[kTriangle]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->tri_.size() * sizeof(Triangle)),
                 reinterpret_cast<GLvoid*>(this->tri_.data()),
                 GL_STATIC_DRAW);
  }
  // Check for error
  err = (glGetError() == GL_NO_ERROR) ? 0 : -1;
  // Make sure the VAO is not changed from the outside
  glBindVertexArray(0);
  return err;
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @name Bind
 *  @fn void Bind(void)
 *  @brief  Bind vertex array object for drawing
 */
template<typename T>
void OGLMesh<T>::Bind(void) {
  glBindVertexArray(vao_);
}

/*
 *  @name Unbind
 *  @fn void Unbind(void)
 *  @brief  Unbind vertex array object
 */
template<typename T>
void OGLMesh<T>::Unbind(void) {
  glBindVertexArray(0);
}
  
#pragma mark -
#pragma mark Declaration
  
/** OGLMesh - FLoat */
template class OGLMesh<float>;

/** OGLMesh - Double */
template class OGLMesh<double>;
  
}  // namespace CHLib
