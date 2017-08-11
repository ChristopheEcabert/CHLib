/**
 *  @file   callbacks.hpp
 *  @brief  OpenGL callbacks interface definition
 *          Based on : http://ogldev.atspace.co.uk/
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_CALLBACKS__
#define __OGLKIT_CALLBACKS__

#include <chrono>

#include "oglkit/ogl/key_types.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
/**
 *  @class   OGLCallbacks
 *  @brief   Unified for OpenGL backend.
 *          Based on : http://ogldev.atspace.co.uk/
 *  @author  Christophe Ecabert
 *  @date    10/02/16
 *  @ingroup ogl
 */
class OGLCallbacks {
  
  public :
  
#pragma mark -
#pragma mark Type definitions
  /** Time point */
  using TimePoint = std::chrono::high_resolution_clock::time_point;
  
#pragma mark -
#pragma mark Initialization
  
  /**
   * @name  OGLCallbacks
   * @fn    OGLCallbacks()
   * @brief Constructor
   */
  OGLCallbacks(void) : delta_time_(0.f) {
    // Get starting time to avoid large delta time
    last_time_ = std::chrono::high_resolution_clock::now();
  }
  
  /**
   * @name  ~OGLCallbacks
   * @fn    virtual ~OGLCallbacks()
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
   * @name  OGLMouseCb
   * @fn  virtual void OGLMouseCb(const OGLMouse& button, 
                                  const OGLKeyState& state,
                                  const float x,
                                  const float y)
   * @brief Callback invoked when mouse is clicked
   * @param[in] button  Button that trigger the callback
   * @param[in] state   Button's state at that time
   * @param[in] x       Mouse's X coordinate
   * @param[in] y       Mouse's Y coordinate
   */
  virtual void OGLMouseCb(const OGLMouse& button,
                          const OGLKeyState& state,
                          const float x,
                          const float y) {}
  
  /**
   * @name  OGLRenderCb
   * @fn  virtual void OGLRenderCb(void)
   * @brief Callback invoked when scene need to be rendered
   */
  virtual void OGLRenderCb(void) {}
  
  /**
   *  @name OGLResizeCb
   *  @fn virtual void OGLResizeCb(const float width, const float height)
   *  @brief  Callback invoked when the view is resized
   *  @param[in]  width   New width of the view
   *  @param[in]  height  New height of the view
   */
  virtual void OGLResizeCb(const float width, const float height) {}
  
  /**
   *  @name OGLStart
   *  @fn void OGLStart(void)
   *  @brief  Start rendering loop
   */
  void OGLStart(void) {
    namespace chrono = std::chrono;
    using clock = chrono::high_resolution_clock;
    using ms = chrono::milliseconds;
    current_time_ = clock::now();
    delta_time_ = chrono::duration_cast<ms>(current_time_ - last_time_).count();
  }
  
  /**
   *  @name OGLStop
   *  @fn void OGLStop(void)
   *  @brief  Stop rendering loop
   */
  void OGLStop(void) {
    last_time_ = current_time_;
  }
  
 protected:
  /** Current time */
  TimePoint current_time_;
  /** Last time */
  TimePoint last_time_;
  /** Delta time in milliseconds */
  float delta_time_;
};
  
}  // namespace OGLKit
#endif /* __OGLKIT_CALLBACKS__ */
