/**
 *  @file   callbacks.hpp
 *  @brief  OpenGL callbacks interface definition
 *          Based on : http://ogldev.atspace.co.uk/
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_CALLBACKS__
#define __CHLIB_CALLBACKS__

#include "chlib/ogl/key_types.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 * @class   OGLCallback
 * @brief   Unified for OpenGL backend.
 *          Based on : http://ogldev.atspace.co.uk/
 * @author  Christophe Ecabert
 * @date    10/02/16
 */
class OGLCallbacks {
  
  public :
#pragma mark -
#pragma mark Initialization
  
  /**
   * @name  ~OGLCallback
   * @fn    virtual ~OGLCallback()
   * @brief Destructor
   */
  virtual ~OGLCallbacks() {}
  
#pragma mark -
#pragma mark Callbacks
  
  /**
   * @name  OGLKeyboardCb
   * @fn  virtual void OGLKeyboardCb(const OGLKey& key,
   *                                 const OGLKeyState& state)
   * @brief Callback for keyboard event
   * @param[in] key     Key that trigger the callback
   * @param[in] state   Key state at that time
   */
  virtual void OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state) {}
  
  /**
   * @name  OGLPassiveMouseCb
   * @fn  virtual void OGLPassiveMouseCb(const float x, const float y)
   * @brief Callback handling mouse movement inside OpenGL window
   * @param[in] x   Mouse's X coordinate
   * @param[in] y   Mouse's Y coordinate
   */
  virtual void OGLPassiveMouseCb(const float x, const float y) {}
  
  /**
   * @name  OGLRenderCb
   * @fn  virtual void OGLRenderCb(void)
   * @brief Callback invoked when scene need to be rendered
   */
  virtual void OGLRenderCb(void) {}
  
  /**
   * @name  OGLMouseCb
   * @fn  virtual void OGLMouseCb(const OGLMouse& button, 
                                  const OGLKeyState& state,
                                  const float x,
                                  const float y)
   * @brief
   * @param[in] button  Button that trigger the callback
   * @param[in] state   Button's state at that time
   * @param[in] x       Mouse's X coordinate
   * @param[in] y       Mouse's Y coordinate
   */
  virtual void OGLMouseCb(const OGLMouse& button,
                          const OGLKeyState& state,
                          const float x,
                          const float y) {}
};
  
}  // namespace CHLib
#endif /* __CHLIB_CALLBACKS__ */
