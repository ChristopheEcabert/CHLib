/**
 *  @file   app02.hpp
 *  @brief  Texture concept
 *
 *  @author Christophe Ecabert
 *  @date   05/03/17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_APP02__
#define __OGLKIT_APP02__

#include "base_app.hpp"

#include "oglkit/ogl/ogl_mesh.hpp"
#include "oglkit/ogl/shader.hpp"
#include "oglkit/ogl/camera.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
/**
 *  @class  App02
 *  @brief  Debug class
 *  @author Christophe Ecabert
 *  @date   05/03/17
 */
class App02 : public BaseApp {
 public:
 
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name App02
   *  @fn App02(void)
   *  @brief  Constructor
   *  @param[in]  win_width   View's width
   *  @param[in]  win_height  View's height
   */
  App02(const float win_width, const float win_height);
  
  /**
   *  @name App02
   *  @fn App02(const App02& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy from
   */
  App02(const App02& other) = delete;
  
  /**
   *  @name operator=
   *  @fn App02& operator=(const App02& rhs) = delete;
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  App02& operator=(const App02& rhs) = delete;
  
  /**
   *  @name ~App02
   *  @fn ~App02(void)
   *  @brief  Destructor
   */
  ~App02(void);
  
  /**
   *  @name Load
   *  @fn int Load(const std::string& config) = 0
   *  @brief  Initialize application (i.e. Scene)
   *  @param[in]  config  Path to the scene configuration file
   *  @return -1 if error, 0 otherwise
   */
  int Load(const std::string& config);
  
#pragma mark -
#pragma mark Callbacks
  
  /**
   * @name  OGLKeyboardCb
   * @fn  void OGLKeyboardCb(const OGLKey& key,
   *                                 const OGLKeyState& state)
   * @brief Callback for keyboard event
   * @param[in] key     Key that trigger the callback
   * @param[in] state   Key state at that time
   */
  void OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state);
  
  /**
   * @name  OGLRenderCb
   * @fn  void OGLRenderCb(void)
   * @brief Callback invoked when scene need to be rendered
   */
  void OGLRenderCb(void);
  
  /**
   * @name  OGLPassiveMouseCb
   * @fn  void OGLPassiveMouseCb(const float x, const float y)
   * @brief Callback handling mouse movement inside OpenGL window
   * @param[in] x   Mouse's X coordinate
   * @param[in] y   Mouse's Y coordinate
   */
  void OGLPassiveMouseCb(const float x, const float y);
  
  /**
   * @name  OGLMouseCb
   * @fn  void OGLMouseCb(const OGLMouse& button,
   const OGLKeyState& state,
   const float x,
   const float y)
   * @brief Callback invoked when mouse is clicked
   * @param[in] button  Button that trigger the callback
   * @param[in] state   Button's state at that time
   * @param[in] x       Mouse's X coordinate
   * @param[in] y       Mouse's Y coordinate
   */
  void OGLMouseCb(const OGLMouse& button,
                  const OGLKeyState& state,
                  const float x,
                  const float y);
  
  /**
   *  @name OGLResize
   *  @fn void OGLResize(const float widht, const float hieght)
   *  @brief  Callbkac invoked when view resize
   *  @param[in]  width   View's width
   *  @param[in]  height  View's height
   */
  void OGLResizeCb(const float width, const float height);
  
#pragma mark -
#pragma mark Private
 private:
  /** Mesh */
  OGLMesh<float>* mesh_;
  /** Camera */
  OGLCamera<float>* camera_;
  /** Technique */
  OGLShader* shader_;
};
  
/**
 *  @class  App02Proxy
 *  @brief  App00 Proxy
 *  @author Christophe Ecabert
 *  @date 15.07.17
 *  @ingroup app
 */
class App02Proxy : public AppProxy {
public:
  
  /**
   *  @name App02Proxy
   *  @fn App02Proxy(void);
   *  @brief  Constructor
   */
  App02Proxy(void);
  
  /**
   *  @name App02Proxy
   *  @fn App02Proxy(void);
   *  @brief  Constructor
   */
  ~App02Proxy(void);
  
  /**
   *  @name Create
   *  @fn BaseApp* Create(const float width, const float height) const
   *  @brief  Create an app of a given type
   *  @param[in]  width Window's width    Window's width
   *  @param[in]  height Window's height  Window's height
   */
  BaseApp* Create(const float width, const float height) const;
  
  /**
   *  @name Id
   *  @fn size_t Id(void) const
   *  @brief  Provide ID of the app
   *  @return App's ID
   */
  size_t Id(void) const;
  
  /**
   *  @name Name
   *  @fn const char* Name(void) const
   *  @brief  Provide Name of the app
   *  @return App's name
   */
  const char* Name(void) const;
};
}  // namespace OGLKit
#endif /* __OGLKIT_APP02__ */
