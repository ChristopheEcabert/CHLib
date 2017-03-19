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

#include "chlib/core/library_export.hpp"
#include "chlib/geometry/mesh.hpp"
#include "chlib/ogl/texture.hpp"
#include "chlib/ogl/shader.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {

/** Context forwarding */
struct OGLMeshContext;
  
/**
 *  @class  OGLMesh
 *  @brief  3D Mesh container with drawing capability
 *  @author Christophe Ecabert
 *  @date   02/08/16
 */
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
   *  @fn void Bind(void) const
   *  @brief  Bind vertex array object for drawing
   */
  void Bind(void) const;
  
  /**
   *  @name Render
   *  @fn void Render(const OGLShader& shader) const
   *  @brief  Render the object
   *  @param[in] shader Shader to use while rendering
   */
  void Render(const OGLShader& shader) const;
  
  /**
   *  @name Unbind
   *  @fn void Unbind(void) const
   *  @brief  Unbind vertex array object
   */
  void Unbind(void) const;
  
#pragma mark -
#pragma mark Accessors
  
  /**
   *  @name set_texture
   *  @fn void set_texture(const std::vector<OGLTexture*>& texture)
   *  @brief  Add texture
   *  @param[in]  texture List of texture
   */
  void set_texture(const std::vector<OGLTexture*>& texture) {
    textures_ = texture;
  }
  
  /**
   *  @name get_texture
   *  @fn std::vector<OGLTexture*>& get_texture(void)
   *  @brief  Get texture
   *  @return List of texture
   */
  std::vector<OGLTexture*>& get_texture(void) {
    return textures_;
  }
  
  /**
   *  @name get_texture
   *  @fn const std::vector<OGLTexture*>& get_texture(void) const
   *  @brief  Get texture
   *  @return List of texture
   */
  const std::vector<OGLTexture*>& get_texture(void) const {
    return textures_;
  }
  
#pragma mark -
#pragma mark Private
 private:
  
  /** OpenGL Context */
  OGLMeshContext* ctx_;
  /** Textures */
  std::vector<OGLTexture*> textures_;
};
}  // namespace CHLib
#endif /* __CHLIB_OGL_MESH__ */
