/**
 *  @file   scene.hpp
 *  @brief  High level abstraction representing the content of a scene. The 
 *          scene stands for all what is displayed on the screen as well as all
 *          parameters needed to render it such as shaders, lights, camera
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   07.08.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_SCENE__
#define __OGLKIT_SCENE__

#include "oglkit/core/library_export.hpp"
#include "oglkit/ogl/camera.hpp"
#include "oglkit/ogl/shader.hpp"
#include "oglkit/ogl/transform.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
  struct XMLReader;
  
  /**
   *  @class  OGLScene
   *  @brief  High level abstraction representing the content of a scene
   *  @author Christophe Ecabert
   *  @date   07.08.17
   *  @ingroup ogl
   */
template<typename T>
class OGLKIT_EXPORTS OGLScene {
 public:
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name OGLScene
   *  @fn OGLScene(void)
   *  @brief  Constructor
   */
  OGLScene(void);
  
  /**
   *  @name OGLScene
   *  @fn OGLScene(const OGLScene& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy from
   */
  OGLScene(const OGLScene& other) = delete;
  
  /**
   *  @name   operator=
   *  @fn     OGLScene& operator=(const OGLScene& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in] rhs  Object to assign from
   *  @return Newly assigned object
   */
  OGLScene& operator=(const OGLScene& rhs) = delete;
  
  /**
   *  @name ~OGLScene
   *  @fn ~OGLScene(void)
   *  @brief Destructor
   */
  ~OGLScene(void);
  
  /**
   *  @name   LoadFromFile
   *  @fn     int LoadFromFile(const std::string& filename)
   *  @brief  Load a scene from a given *.xml file
   *  @param[in] filename Path to a xml file
   *  @return -1 if error, 0 otherwise
   */
  int LoadFromFile(const std::string& filename);
  
  /**
   *  @name   LoadFromString
   *  @fn     int LoadFromString(const std::string& scene_str)
   *  @brief  Load a scene from a given string. Internally parse it and 
   *          construct the scene
   *  @param[in] scene_str  String holding scene description in xml format.
   *  @return -1 if error, 0 otherwise
   */
  int LoadFromString(const std::string& scene_str);
  
#pragma mark -
#pragma mark Usage

  /**
   *  @name   AddCamera
   *  @fn     void AddCamera(const OGLCamera<T>* camera)
   *  @brief  Add a camera to the scene. TAKE ownership of the object
   *  @param[in] camera Camera object to add to the scene
   */
  void AddCamera(const OGLCamera<T>* camera);
  
  /**
   *  @name   AddShader
   *  @fn     void AddShader(const OGLShader* shader)
   *  @brief  Add a shader to the scene. TAKE ownership of the object
   *  @param[in]  shader Shader to add to the scene
   */
  void AddShader(const OGLShader* shader);
  
  /**
   *  @name   AddTransform
   *  @fn     void AddTransform(const OGLTransform<T>* shader)
   *  @brief  Add a transform to the scene. TAKE ownership of the object
   *  @param[in]  transform Object transformation to add to the scene
   */
  void AddTransform(const OGLTransform<T>& transform);
  
  
#pragma mark -
#pragma mark Private
 private:
  
  /** Vector */
  using Vec3 = Vector3<T>;
  
  /**
   *  @name CreateCamera
   *  @fn OGLCamera<T>* CreateCamera(const XMLReader* reader)
   *  @brief  Construct a camera object from scene file.
   *  @param[in]  reader  Document reader
   *  @return Newly created camera, or nullptr if something went wrong.
   */
  OGLCamera<T>* CreateCamera(const XMLReader* reader) const;
  
  /** Camera */
  OGLCamera<T>* cam_;
  
};

}  // namespace OGLKit
#endif /* __OGLKIT_SCENE__ */
