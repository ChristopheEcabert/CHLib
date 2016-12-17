/**
 *  @file   app01.cpp
 *  @brief  Basic lighting
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include "app01.hpp"


/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Initialization

/*
 *  @name App01
 *  @fn App01(void)
 *  @brief  Constructor
 *  @param[in]  win_width   View's width
 *  @param[in]  win_height  View's height
 */
App01::App01(const float win_width, const float win_height) : BaseApp(win_width,
                                                                      win_height) {
}

/*
 *  @name ~App01
 *  @fn ~App01(void)
 *  @brief  Destructor
 */
App01::~App01(void) {
  
}

/*
 *  @name Load
 *  @fn int Load(const std::string& config) = 0
 *  @brief  Initialize application (i.e. Scene)
 *  @param[in]  config  Path to the scene configuration file
 *  @return -1 if error, 0 otherwise
 */
int App01::Load(const std::string& config) {
  int err = -1;
  return err;
}

#pragma mark -
#pragma mark Callbacks

/*
 * @name  OGLKeyboardCb
 * @fn  void OGLKeyboardCb(const OGLKey& key,
 *                                 const OGLKeyState& state)
 * @brief Callback for keyboard event
 * @param[in] key     Key that trigger the callback
 * @param[in] state   Key state at that time
 */
void App01::OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state) {
  
}

/*
 * @name  OGLRenderCb
 * @fn  void OGLRenderCb(void)
 * @brief Callback invoked when scene need to be rendered
 */
void App01::OGLRenderCb(void) {
  glClearColor(0.7f, 0.0f, 0.0f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
  
}  // namespace CHLib
