/**
 *  @file   ogl_mesh.hpp
 *  @brief  OpenGL Mesh interface
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_OGL_MESH__
#define __CHLIB_OGL_MESH__

#ifdef __APPLE__
  #include <OpenGL/gl3.h>
#endif

#include "chlib/core/library_export.hpp"
#include "chlib/geometry/mesh.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
template<typename T>
class CHLIB_EXPORTS OGLMesh : public CHLib::Mesh<T> {
  
 public:
  
#pragma mark -
#pragma mark Type definition
  
  /** Vertex */
  using Vertex = typename CHLib::Mesh<T>::Vertex;
  /** Edge */
  using Edge = typename CHLib::Mesh<T>::Edge;
  /** Normal */
  using Normal = typename CHLib::Mesh<T>::Normal;
  /** Texture coordinate */
  using TCoord = typename CHLib::Mesh<T>::TCoord;
  /** Vertex color */
  using Color = typename CHLib::Mesh<T>::Color;
  /** Tangente space */
  using Tangent = typename CHLib::Mesh<T>::Tangent;
  /** Triangle */
  using Triangle = typename CHLib::Mesh<T>::Triangle;
  
#pragma mark - 
#pragma mark Initialization
  
  /**
   *  @name OGLMesh
   *  @fn OGLMesh(void)
   *  @brief  Constructor
   */
  OGLMesh(void);
  
  /**
   *  @name OGLMesh
   *  @fn OGLMesh(const OGLMesh& other) = delete
   *  @brief  Copy constructor
   */
  OGLMesh(const OGLMesh& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLMesh& operator=(const OGLMesh& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  OGLMesh& operator=(const OGLMesh& rhs) = delete;
  
  /**
   *  @name ~OGLMesh
   *  @fn ~OGLMesh(void)
   *  @brief  Destructor
   */
  ~OGLMesh(void);
  
  /**
   *  @name InitOpenGLContext
   *  @fn int InitOpenGLContext(void)
   *  @brief  Allocate buffer and push data onto OpenGL context
   *  @return -1 if error, 0 otherwise
   */
  int InitOpenGLContext(void);
  
#pragma mark -
#pragma mark Usage
  
  /** 
   *  @name Bind
   *  @fn void Bind(void)
   *  @brief  Bind vertex array object for drawing
   */
  void Bind(void);
  
  /**
   *  @name Unbind
   *  @fn void Unbind(void)
   *  @brief  Unbind vertex array object
   */
  void Unbind(void);
  
#pragma mark -
#pragma mark Accessors
  
#pragma mark -
#pragma mark Private
 private:
  
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
  
  /** Vertex array object */
  GLuint vao_;
  /** Buffer object */
  GLuint vbo_[6];

  
};
  
}  // namespace CHLib






#endif /* __CHLIB_OGL_MESH__ */
