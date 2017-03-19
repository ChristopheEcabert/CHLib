/**
 *  @file   mesh.cpp
 *  @brief
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#include "chlib/ogl/ogl_mesh.hpp"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Type definition
  
/**
 *  @struct OGLMeshContext
 *  @brief  OpenGL context for mesh object
 */
struct OGLMeshContext {
  
  /**
   *  @enum   BufferType
   *  @brief  List of OpenGL buffer in the VAO
   */
  enum BufferType {
    /** Vertex buffer */
    kVertex = 0,
    /** Normal buffer */
    kNormal = 1,
    /** Texture coordinate */
    kTCoord = 2,
    /** Vertex color */
    kColor = 3,
    /** Tangent space */
    kTangent = 4,
    /** Triangle buffer */
    kTriangle = 5
  };
  
  /** Vertex Array Object */
  GLuint vao;
  /** Buffer object */
  GLuint vbo[6];
  
  /** 
   *  @name OGLMeshContext
   *  @fn OGLMeshContext(void)
   *  @brief  Constructor
   */
  OGLMeshContext(void) : vao(0), vbo{0} {
    // Lazy init
    glGenVertexArrays(1, &vao);
    // Init buffers
    glBindVertexArray(vao);
    glGenBuffers(sizeof(vbo)/sizeof(vbo[0]), &vbo[0]);
    // Unbind
    glBindVertexArray(0);
  }
  
  /**
   *  @name OGLMeshContext
   *  @fn ~OGLMeshContext(void)
   *  @brief  Constructor
   */
  ~OGLMeshContext(void) {
    // Clear buffer
    if (vbo[0] != 0) {
      // Ensure VBO is unbind
      glBindVertexArray(vao);
      glDeleteBuffers(6, &vbo[0]);
      memset(reinterpret_cast<void*>(&vbo[0]),
             0,
             sizeof(vbo) / sizeof(vbo[0]));
      glBindVertexArray(0);
    }
    // Clear vao
    if (vao) {
      glDeleteVertexArrays(1, &vao);
      vao = 0;
    }
  }
};
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name OGLMesh
 *  @fn OGLMesh(void)
 *  @brief  Constructor
 */
template<typename T>
OGLMesh<T>::OGLMesh(void) : Mesh<T>() {
  // Init context
  ctx_ = new OGLMeshContext();
}

/*
 *  @name ~OGLMesh
 *  @fn ~OGLMesh(void)
 *  @brief  Destructor
 */
template<typename T>
OGLMesh<T>::~OGLMesh(void) {
  if (ctx_) {
    delete ctx_;
    ctx_ = nullptr;
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
    using BufferType = OGLMeshContext::BufferType;
  
  int err = -1;
  glBindVertexArray(ctx_->vao);
  // Init buffers, VERTEX
  GLenum data_t = sizeof(T) == 4 ? GL_FLOAT : GL_DOUBLE;
  if (this->vertex_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, ctx_->vbo[BufferType::kVertex]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->vertex_.size() * sizeof(Vertex)),
                 reinterpret_cast<GLvoid*>(this->vertex_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(BufferType::kVertex);
    glVertexAttribPointer(BufferType::kVertex, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Normal
  if (this->normal_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, ctx_->vbo[BufferType::kNormal]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->normal_.size() * sizeof(Normal)),
                 reinterpret_cast<GLvoid*>(this->normal_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(BufferType::kNormal);
    glVertexAttribPointer(BufferType::kNormal, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Texture coordinate
  if (this->tex_coord_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, ctx_->vbo[BufferType::kTCoord]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->tex_coord_.size() * sizeof(TCoord)),
                 reinterpret_cast<GLvoid*>(this->tex_coord_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(BufferType::kTCoord);
    glVertexAttribPointer(BufferType::kTCoord, 2, data_t, GL_FALSE, 0, NULL);
  }
  // Tangent space
  if (this->tangent_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, ctx_->vbo[BufferType::kTangent]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->tangent_.size() * sizeof(Tangent)),
                 reinterpret_cast<GLvoid*>(this->tangent_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(BufferType::kTangent);
    glVertexAttribPointer(BufferType::kTangent, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Vertex color
  if (this->vertex_color_.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, ctx_->vbo[BufferType::kColor]);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(this->vertex_color_.size() * sizeof(Color)),
                 reinterpret_cast<GLvoid*>(this->vertex_color_.data()),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(BufferType::kColor);
    glVertexAttribPointer(BufferType::kColor, 3, data_t, GL_FALSE, 0, NULL);
  }
  // Triangle
  if (this->tri_.size() > 0) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx_->vbo[BufferType::kTriangle]);
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
void OGLMesh<T>::Bind(void) const {
  glBindVertexArray(ctx_->vao);
}
  
/*
 *  @name Render
 *  @fn void Render(const OGLShader& shader) const
 *  @brief  Render the object
 *  @param[in] shader Shader to use while rendering
 */
template<typename T>
void OGLMesh<T>::Render(const OGLShader& shader) const {
  
  // Activate texture if any
  int cnt_normal = 0;
  int cnt_diffuse = 0;
  int cnt_specular = 0;
  int idx = 0;
  for (int i = 0; i < textures_.size(); ++i) {
    const auto* tex = textures_[i];
    // Activate + bind
    tex->Bind(i);
    // Set uniform
    if (tex->get_type() == OGLTexture::Type::kDiffuse) {
      idx = cnt_diffuse++;
    } else if(tex->get_type() == OGLTexture::Type::kNormal) {
      idx = cnt_normal++;
    } else {
      idx = cnt_specular++;
    }
    std::string name = "texture_material[" + std::to_string(idx) + "].";
    name += tex->get_type_str();
    shader.SetUniform(name.c_str(), i);
  }
  
  // Bind
  this->Bind();
  
  // Render triangles
  glDrawElementsBaseVertex(GL_TRIANGLES,
                           static_cast<GLsizei>(this->tri_.size() * 3),
                           GL_UNSIGNED_INT,
                           0,
                           0);
  
  // Unbind
  this->Unbind();
  
  for (int i = 0; i < textures_.size(); ++i) {
    textures_[i]->Unbind();
  }
}

/*
 *  @name Unbind
 *  @fn void Unbind(void)
 *  @brief  Unbind vertex array object
 */
template<typename T>
void OGLMesh<T>::Unbind(void) const {
  glBindVertexArray(0);
}
  
#pragma mark -
#pragma mark Declaration
  
/** OGLMesh - FLoat */
template class OGLMesh<float>;

/** OGLMesh - Double */
template class OGLMesh<double>;
  
}  // namespace CHLib
