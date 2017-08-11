/**
 *  @file   app04.cpp
 *  @brief  Basic Lighting
 *
 *  @author Christophe Ecabert
 *  @date   08/08/17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include "app04.hpp"

#include "oglkit/core/string_util.hpp"
#include "oglkit/ogl/texture_manager.hpp"


/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Initialization

/*
 *  @name App04
 *  @fn App04(void)
 *  @brief  Constructor
 *  @param[in]  win_width   View's width
 *  @param[in]  win_height  View's height
 */
App04::App04(const float win_width, const float win_height) {
  // Scene
  this->scene_ = new OGLScene<float>();
}

/*
 *  @name ~App04
 *  @fn ~App04(void)
 *  @brief  Destructor
 */
App04::~App04(void) {
  if (scene_) {
    delete scene_;
    scene_ = nullptr;
  }
}

/*
 *  @name Load
 *  @fn int Load(const std::string& config) = 0
 *  @brief  Initialize application (i.e. Scene)
 *  @param[in]  config  Path to the scene configuration file
 *  @return -1 if error, 0 otherwise
 */
int App04::Load(const std::string& config) {
  int err = -1;
  // Load mesh
  err = this->scene_->LoadFromFile(config);
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
void App04::OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state) {
  // Pass event to camera
  //this->camera_->OnKeyboard(key, state, this->delta_time_);
}

/*
 * @name  OGLRenderCb
 * @fn  void OGLRenderCb(void)
 * @brief Callback invoked when scene need to be rendered
 */
void App04::OGLRenderCb(void) {
  // Clear
  // Enable program
  //this->shader_->Use();
  //this->shader_->SetUniform("camera", camera_->get_transform());
  // Draw triangle
  //this->model_->Render(*this->shader_);
  // Stop program
  //this->shader_->StopUsing();
}
  
/*
 * @name  OGLPassiveMouseCb
 * @fn  void OGLPassiveMouseCb(const float x, const float y)
 * @brief Callback handling mouse movement inside OpenGL window
 * @param[in] x   Mouse's X coordinate
 * @param[in] y   Mouse's Y coordinate
 */
void App04::OGLPassiveMouseCb(const float x, const float y) {
  //this->camera_->OnMouseMove(static_cast<int>(x), static_cast<int>(y));
}

/*
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
void App04::OGLMouseCb(const OGLMouse& button,
                       const OGLKeyState& state,
                       const float x,
                       const float y) {
  /*this->camera_->OnMouseClick(button,
                              state,
                              static_cast<int>(x),
                              static_cast<int>(y));*/
}

/*
 *  @name OGLResize
 *  @fn void OGLResize(const float widht, const float hieght)
 *  @brief  Callbkac invoked when view resize
 *  @param[in]  width   View's width
 *  @param[in]  height  View's height
 */
void App04::OGLResizeCb(const float width, const float height) {
  // Update camera
  //this->camera_->set_window_dimension(width, height);
  //this->camera_->UpdateProjectionTransform();
}
  
#pragma mark -
#pragma mark Registration
  
/*
 *  @name App04Proxy
 *  @fn App04Proxy(void);
 *  @brief  Constructor
 */
App04Proxy::App04Proxy(void) : AppProxy() {}

/*
 *  @name App04Proxy
 *  @fn App04Proxy(void);
 *  @brief  Constructor
 */
App04Proxy::~App04Proxy(void) {}

/*
 *  @name Create
 *  @fn BaseApp* Create(const float width, const float height) const
 *  @brief  Create an app of a given type
 *  @param[in]  width Window's width    Window's width
 *  @param[in]  height Window's height  Window's height
 */
BaseApp* App04Proxy::Create(const float width, const float height) const {
  return new App04(width, height);
}

/*
 *  @name Id
 *  @fn size_t Id(void) const
 *  @brief  Provide ID of the app
 *  @return App's ID
 */
size_t App04Proxy::Id(void) const {
  return 4;
}

/*
 *  @name Name
 *  @fn const char* Name(void) const
 *  @brief  Provide Name of the app
 *  @return App's name
 */
const char* App04Proxy::Name(void) const {
  return "Basic Lighting";
}

// Explicit registration
App04Proxy app04_proxy;
  
}  // namespace OGLKit
