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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "app00.hpp"
#include "chlib/core/string_util.hpp"


/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name App00
 *  @fn App00(void)
 *  @brief  Constructor
 */
App00::App00(void) {
  // Mesh
  mesh_ = new CHLib::OGLMesh<float>();
  // Camera
  camera_ = new CHLib::OGLCamera();
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
    camera_->LookAt(Vector3<float>(0.f, 0.1f, 0.4f),
                    Vector3<float>(0.f, 0.1f, 0.f));

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
  
}  // namespace CHLib
