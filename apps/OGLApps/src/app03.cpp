/**
 *  @file   app03.cpp
 *  @brief  OpenGL Model loader
 *
 *  @author Christophe Ecabert
 *  @date   13/03/17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include "app03.hpp"

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
 *  @name App03
 *  @fn App03(void)
 *  @brief  Constructor
 *  @param[in]  win_width   View's width
 *  @param[in]  win_height  View's height
 */
App03::App03(const float win_width, const float win_height) {
  // Model
  this->model_ = new OGLKit::OGLModel<float>();
  // Camera
  this->camera_ = new OGLKit::OGLCamera<float>();
  this->camera_->set_window_dimension(win_width, win_height);
  this->camera_->set_move_speed(0.02f);
  // Technique
  this->shader_ = new OGLKit::OGLShader();
  // Update wrapping mode
  auto mode = OGLTexture::WrappingMode::kRepeat;
  OGLTextureManager::Instance().set_wraping_model(mode);
}

/*
 *  @name ~App03
 *  @fn ~App03(void)
 *  @brief  Destructor
 */
App03::~App03(void) {
  if (model_) {
    delete model_;
    model_ = nullptr;
  }
  if (camera_) {
    delete camera_;
    camera_ = nullptr;
  }
  if (shader_) {
    delete shader_;
    shader_ = nullptr;
  }
}

/*
 *  @name Load
 *  @fn int Load(const std::string& config) = 0
 *  @brief  Initialize application (i.e. Scene)
 *  @param[in]  config  Path to the scene configuration file
 *  @return -1 if error, 0 otherwise
 */
int App03::Load(const std::string& config) {
  int err = -1;
  std::string dir, file, ext;
  OGLKit::StringUtil::ExtractDirectory(config, &dir, &file, &ext);
  // Load mesh
  err = this->model_->Load(dir + "nanosuit.obj");
  if (!err) {
    // Setup technique
    std::vector<std::string> shaders_file = {dir + "app03-vertex-shader.vs",
                                             dir + "app03-fragment-shader.fs"};
    err = this->shader_->Init(shaders_file);
    err |= this->shader_->Finalize();
    // Setup camera
    this->camera_->LookAt(Vector3<float>(0.f, 8.0f, 30.0f),
                          Vector3<float>(0.f, 8.0f, 0.f));
    
    // update uniform
    this->shader_->Use();
    this->shader_->SetUniform("camera", this->camera_->get_transform());
    this->shader_->StopUsing();
  }
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
void App03::OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state) {
  // Pass event to camera
  this->camera_->OnKeyboard(key, state, this->delta_time_);
}

/*
 * @name  OGLRenderCb
 * @fn  void OGLRenderCb(void)
 * @brief Callback invoked when scene need to be rendered
 */
void App03::OGLRenderCb(void) {
  // Clear
  // Enable program
  this->shader_->Use();
  this->shader_->SetUniform("camera", camera_->get_transform());
  // Draw triangle
  this->model_->Render(*this->shader_);
  // Stop program
  this->shader_->StopUsing();
}
  
/*
 * @name  OGLPassiveMouseCb
 * @fn  void OGLPassiveMouseCb(const float x, const float y)
 * @brief Callback handling mouse movement inside OpenGL window
 * @param[in] x   Mouse's X coordinate
 * @param[in] y   Mouse's Y coordinate
 */
void App03::OGLPassiveMouseCb(const float x, const float y) {
  this->camera_->OnMouseMove(static_cast<int>(x), static_cast<int>(y));
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
void App03::OGLMouseCb(const OGLMouse& button,
                       const OGLKeyState& state,
                       const float x,
                       const float y) {
  this->camera_->OnMouseClick(button,
                              state,
                              static_cast<int>(x),
                              static_cast<int>(y));
}

/*
 *  @name OGLResize
 *  @fn void OGLResize(const float widht, const float hieght)
 *  @brief  Callbkac invoked when view resize
 *  @param[in]  width   View's width
 *  @param[in]  height  View's height
 */
void App03::OGLResizeCb(const float width, const float height) {
  // Update camera
  this->camera_->set_window_dimension(width, height);
  this->camera_->UpdateProjectionTransform();
}
  
#pragma mark -
#pragma mark Registration
  
/*
 *  @name App03Proxy
 *  @fn App03Proxy(void);
 *  @brief  Constructor
 */
App03Proxy::App03Proxy(void) : AppProxy() {}

/*
 *  @name App03Proxy
 *  @fn App03Proxy(void);
 *  @brief  Constructor
 */
App03Proxy::~App03Proxy(void) {}

/*
 *  @name Create
 *  @fn BaseApp* Create(const float width, const float height) const
 *  @brief  Create an app of a given type
 *  @param[in]  width Window's width    Window's width
 *  @param[in]  height Window's height  Window's height
 */
BaseApp* App03Proxy::Create(const float width, const float height) const {
  return new App03(width, height);
}

/*
 *  @name Id
 *  @fn size_t Id(void) const
 *  @brief  Provide ID of the app
 *  @return App's ID
 */
size_t App03Proxy::Id(void) const {
  return 3;
}

/*
 *  @name Name
 *  @fn const char* Name(void) const
 *  @brief  Provide Name of the app
 *  @return App's name
 */
const char* App03Proxy::Name(void) const {
  return "Model Loader";
}

// Explicit registration
App03Proxy app03_proxy;
  
}  // namespace OGLKit
