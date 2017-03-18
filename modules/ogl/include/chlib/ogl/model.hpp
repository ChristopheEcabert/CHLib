/**
 *  @file   model.hpp
 *  @brief  3D Model, composition of OGLMesh + OGLTexture
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_OGL_MODEL__
#define __CHLIB_OGL_MODEL__

#include <vector>

#include "chlib/core/library_export.hpp"
#include "chlib/ogl/ogl_mesh.hpp"
#include "chlib/ogl/texture.hpp"
#include "chlib/ogl/shader.hpp"

/** aiScene type forwarding */
struct aiScene;

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  OGLModel
 *  @brief  3D Model
 *  @author Christophe Ecabert
 *  @date   11.03.17
 */
template<typename T>
class CHLIB_EXPORTS OGLModel {
 public:
  
#pragma mark -
#pragma mark Initialization
  
  /** Mesh */
  using OGLMesh = typename CHLib::OGLMesh<T>;
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name   OGLModel
   *  @fn     OGLModel(void)
   *  @brief  Constructor
   */
  OGLModel(void);
  
  /**
   *  @name   ~OGLModel
   *  @fn     ~OGLModel(void)
   *  @brief  Destructor
   */
  ~OGLModel(void);
  
  /**
   *  @name   OGLModel
   *  @fn     OGLModel(const OGLModel& other) = delete
   *  @brief  Copy constructor
   *  @param[in]  other Object to copy from
   */
  OGLModel(const OGLModel& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLModel& operator=(const OGLModel& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned operator
   */
  OGLModel& operator=(const OGLModel& rhs) = delete;
  
  /** 
   *  @name Load
   *  @fn int Load(const std::string& filename)
   *  @brief  Load model into memory
   *  @param[in]  filename  Path to the model
   *  @return -1 if error, 0 otherwise
   */
  int Load(const std::string& filename);
  
#pragma mark -
#pragma mark Usage
  
  /**
   *  @name Render
   *  @fn void Render(const OGLShader& shader)
   *  @brief  Render the model
   *  @param[in]  shader  Shader to use while drawing
   */
  void Render(const OGLShader& shader);
  
#pragma mark -
#pragma mark Private
 private:
  
  /** 
   *  @name ProcessScene
   *  @fn int ProcessScene(const aiScene& scene)
   *  @brief  Process Assimp scene and convert to OGLModel format
   *  @param[in]  scene Scene to process
   *  @return -1 if error, 0 otherwise
   */
  int ProcessScene(const aiScene& scene);
  
  
  /** Mesh by parts */
  std::vector<OGLMesh*> meshes_;
  /** Folder where scene is stored */
  std::string directory_;
};
  
}  // namespace CHLib


#endif /* __CHLIB_OGL_MODEL__ */
