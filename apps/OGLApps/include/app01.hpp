/**
 *  @file   app01.hpp
 *  @brief  Basic lighting
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_APP01__
#define __CHLIB_APP01__

#include "base_app.hpp"

#include "chlib/ogl/ogl_mesh.hpp"
#include "chlib/ogl/shader.hpp"
#include "chlib/ogl/camera.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  App01
 *  @brief  Debug class
 *  @author Christophe Ecabert
 *  @date   23/08/16
 */
class App01 : public BaseApp {
 public:
 
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name App01
   *  @fn App01(void)
   *  @brief  Constructor
   *  @param[in]  win_width   View's width
   *  @param[in]  win_height  View's height
   */
  App01(const float win_width, const float win_height);
  
  /**
   *  @name App01
   *  @fn App01(const App01& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy from
   */
  App01(const App01& other) = delete;
  
  /**
   *  @name operator=
   *  @fn App01& operator=(const App01& rhs) = delete;
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  App01& operator=(const App01& rhs) = delete;
  
  /**
   *  @name ~App01
   *  @fn ~App01(void)
   *  @brief  Destructor
   */
  ~App01(void);
  
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
  OGLCamera* camera_;
  /** Technique */
  OGLShader* shader_;
};
  
/**
 *  @class  App01Proxy
 *  @brief  App00 Proxy
 *  @author Christophe Ecabert
 *  @date 15.07.17
 *  @ingroup app
 */
class App01Proxy : public AppProxy {
public:
  
  /**
   *  @name App01Proxy
   *  @fn App01Proxy(void);
   *  @brief  Constructor
   */
  App01Proxy(void);
  
  /**
   *  @name App01Proxy
   *  @fn App01Proxy(void);
   *  @brief  Constructor
   */
  ~App01Proxy(void);
  
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
}  // namespace CHLib
#endif /* __CHLIB_APP01__ */
