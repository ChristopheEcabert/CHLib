/**
 *  @file   app00.cpp
 *  @brief  Debug apps
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include "app00.hpp"
#include "chlib/core/string_util.hpp"

#include "chlib/core/math/quaternion.hpp"


/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name App00
 *  @fn App01(void)
 *  @brief  Constructor
 *  @param[in]  win_width   View's width
 *  @param[in]  win_height  View's height
 */
App00::App00(const float win_width, const float win_height) :
  BaseApp(win_width, win_height) {
  // Mesh
  mesh_ = new CHLib::OGLMesh<float>();
  // Camera
  camera_ = new CHLib::OGLCamera();
  camera_->set_window_dimension(this->win_width_, this->win_height_);
  // Technique
  technique_ = new CHLib::OGLTechnique();
}

/*
 *  @name ~App00
 *  @fn ~App00(void)
 *  @brief  Destructor
 */
App00::~App00(void) {
  if (mesh_) {
    delete mesh_;
    mesh_ = nullptr;
  }
  if (camera_) {
    delete camera_;
    camera_ = nullptr;
  }
  if (technique_) {
    delete technique_;
    technique_ = nullptr;
  }
}

/*
 *  @name Load
 *  @fn int Load(const std::string& config) = 0
 *  @brief  Initialize application (i.e. Scene)
 *  @param[in]  config  Path to the scene configuration file
 *  @return -1 if error, 0 otherwise
 */
int App00::Load(const std::string& config) {
  int err = -1;
  std::string dir, file, ext;
  CHLib::StringUtil::ExtractDirectory(config, &dir, &file, &ext);
  // Load mesh
  err = mesh_->Load(dir + "bunny.ply");
  mesh_->ComputeVertexNormal();
  err |= mesh_->InitOpenGLContext();
  if (!err) {
    // Setup technique
    std::vector<std::string> shaders_file = {dir + "vertex-shader.vs",
      dir + "fragment-shader.fs"};
    err = technique_->Init(shaders_file);
    err |= technique_->Finalize();
    // Setup camera
    camera_->LookAt(Vector3<float>(0.f, 0.0f, 0.4f),
                    Vector3<float>(0.f, 0.0f, 0.f));

    // update uniform
    technique_->Use();
    technique_->SetUniform("camera", camera_->get_transform());
    technique_->StopUsing();
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
void App00::OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state) {
  // Pass event to camera
  camera_->OnKeyboard(key, state, this->delta_time_);
}

/*
 * @name  OGLRenderCb
 * @fn  void OGLRenderCb(void)
 * @brief Callback invoked when scene need to be rendered
 */
void App00::OGLRenderCb(void) {
  glClearColor(0.f, 0.0f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Enable VAO
  mesh_->Bind();
  // Enable program
  technique_->Use();
  technique_->SetUniform("camera", camera_->get_transform());
  // Draw triangle
  const std::vector<OGLMesh<float>::Triangle>& tri = mesh_->get_triangle();
  glDrawElementsBaseVertex(GL_TRIANGLES,
                           static_cast<GLsizei>(tri.size() * 3),
                           GL_UNSIGNED_INT,
                           0,
                           0);
  // Make sure the VAO is not changed from the outside
  mesh_->Unbind();
  // Stop program
  technique_->StopUsing();
}
  
/*
 * @name  OGLPassiveMouseCb
 * @fn  void OGLPassiveMouseCb(const float x, const float y)
 * @brief Callback handling mouse movement inside OpenGL window
 * @param[in] x   Mouse's X coordinate
 * @param[in] y   Mouse's Y coordinate
 */
void App00::OGLPassiveMouseCb(const float x, const float y) {
  camera_->OnMouseMove(static_cast<int>(x), static_cast<int>(y));
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
void App00::OGLMouseCb(const OGLMouse& button,
                const OGLKeyState& state,
                const float x,
                const float y) {
  camera_->OnMouseClick(button,
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
void App00::OGLResizeCb(const float width, const float height) {
  // Update camera
  this->win_width_ = width;
  this->win_height_ = height;
  camera_->set_window_dimension(this->win_width_, this->win_height_);
  camera_->UpdateProjectionTransform();
}
  
}  // namespace CHLib
