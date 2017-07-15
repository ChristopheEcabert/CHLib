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

#include "chlib/core/string_util.hpp"


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
App01::App01(const float win_width, const float win_height) {
  // Mesh
  this->mesh_ = new CHLib::OGLMesh<float>();
  // Camera
  this->camera_ = new CHLib::OGLCamera();
  this->camera_->set_window_dimension(win_width, win_height);
  // Technique
  this->shader_ = new CHLib::OGLShader();

}

/*
 *  @name ~App01
 *  @fn ~App01(void)
 *  @brief  Destructor
 */
App01::~App01(void) {
  if (this->mesh_) {
    delete mesh_;
    mesh_ = nullptr;
  }
  if (this->camera_) {
    delete camera_;
    camera_ = nullptr;
  }
  if (this->shader_) {
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
int App01::Load(const std::string& config) {
  int err = -1;
  std::string dir, file, ext;
  CHLib::StringUtil::ExtractDirectory(config, &dir, &file, &ext);
  // Load mesh
  err = this->mesh_->Load(dir + "bunny.ply");
  this->mesh_->ComputeVertexNormal();
  err |= this->mesh_->InitOpenGLContext();
  if (!err) {
    // Setup technique
    std::vector<std::string> shaders_file = {dir + "app01-vertex-shader.vs",
                                             dir + "app01-geometry-shader.gs",
                                             dir + "app01-fragment-shader.fs"};
    err = this->shader_->Init(shaders_file);
    err |= this->shader_->Finalize();
    // Setup camera
    this->camera_->LookAt(Vector3<float>(0.f, 0.0f, 0.4f),
                    Vector3<float>(0.f, 0.0f, 0.f));
    
    // update uniform
    this->shader_->Use();
    this->shader_->SetUniform("camera", this->camera_->get_transform());
    this->shader_->SetUniform("time", 0.f);
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
void App01::OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state) {
  // Pass event to camera
  this->camera_->OnKeyboard(key, state, this->delta_time_);
}

/*
 * @name  OGLRenderCb
 * @fn  void OGLRenderCb(void)
 * @brief Callback invoked when scene need to be rendered
 */
void App01::OGLRenderCb(void) {
  using namespace std::chrono;
  
  // Enable VAO
  this->mesh_->Bind();
  // Enable program
  this->shader_->Use();
  this->shader_->SetUniform("camera", camera_->get_transform());
  // Set time
  auto epoch = time_point_cast<milliseconds>(this->current_time_).time_since_epoch();
  float time = epoch.count();
  this->shader_->SetUniform("time", time);
  // Draw triangle
  this->mesh_->Render(*this->shader_);
  // Make sure the VAO is not changed from the outside
  this->mesh_->Unbind();
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
void App01::OGLPassiveMouseCb(const float x, const float y) {
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
void App01::OGLMouseCb(const OGLMouse& button,
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
void App01::OGLResizeCb(const float width, const float height) {
  // Update camera
  this->camera_->set_window_dimension(width, height);
  this->camera_->UpdateProjectionTransform();
}
  
#pragma mark -
#pragma mark Registration
  
/*
 *  @name App01Proxy
 *  @fn App01Proxy(void);
 *  @brief  Constructor
 */
App01Proxy::App01Proxy(void) : AppProxy() {}

/*
 *  @name App01Proxy
 *  @fn App01Proxy(void);
 *  @brief  Constructor
 */
App01Proxy::~App01Proxy(void) {}

/*
 *  @name Create
 *  @fn BaseApp* Create(const float width, const float height) const
 *  @brief  Create an app of a given type
 *  @param[in]  width Window's width    Window's width
 *  @param[in]  height Window's height  Window's height
 */
BaseApp* App01Proxy::Create(const float width, const float height) const {
  return new App01(width, height);
}

/*
 *  @name Id
 *  @fn size_t Id(void) const
 *  @brief  Provide ID of the app
 *  @return App's ID
 */
size_t App01Proxy::Id(void) const {
  return 1;
}

/*
 *  @name Name
 *  @fn const char* Name(void) const
 *  @brief  Provide Name of the app
 *  @return App's name
 */
const char* App01Proxy::Name(void) const {
  return "Geometry Shader";
}

// Explicit registration
App01Proxy app01_proxy;
  
}  // namespace CHLib
