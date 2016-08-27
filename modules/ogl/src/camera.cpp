/**
 *  @file   camera.cpp
 *  @brief  OpenGL Camera abstraction
 *          Based on : http://learnopengl.com/#!Getting-started/Camera
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#include <limits>
#include <assert.h>

#include "chlib/ogl/camera.hpp"
#include "chlib/core/math/vector.hpp"
#include "chlib/core/math/matrix.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {

#pragma mark -
#pragma mark Initialization

/*
 *  @name OGLCamera
 *  @fn OGLCamera(void)
 *  @brief  Constructor
 */
OGLCamera::OGLCamera(void) :  position_(0.f, 0.f, 1.f),
target_(0.f, 0.f, 0.f),
aspect_(1.25f),
near_(0.01f),
far_(100.f),
fov_(M_PI/6.f) {
  // Define view
  this->LookAt(position_, target_);
  // Define projection
  this->UpdateProjectionTransform(fov_, near_, far_, aspect_);
}
  
/*
 *  @name OGLCamera
 *  @fn OGLCamera(void)
 *  @brief  Constructor
 *  @param[in]  position  Where to place the camera
 *  @param[in]  target    Where to point at
 */
OGLCamera::OGLCamera(const Vec3& position, const Vec3& target) :
position_(position),
target_(target),
aspect_(1.25f),
near_(0.01f),
far_(1000.f),
fov_(M_PI/6.f) {
  // Define view
  this->LookAt(position_, target_);
  // Define projection
  this->UpdateProjectionTransform(fov_, near_, far_, aspect_);
}

/*
 *  @name ~OGLCamera
 *  @fn ~OGLCamera(void)
 *  @brief  Destructor
 */
OGLCamera::~OGLCamera(void) {
}
  
/*
 *  @name LookAt
 *  @fn void LookAt(const Vec3& position, const Vec3& target);
 *  @brief  Define view transformation
 *  @param[in]  position  Where to place the camera
 *  @param[in]  target    Where to point at
 */
void OGLCamera::LookAt(const Vec3& position, const Vec3& target) {
  // Define target direction
  position_ = position;
  target_ = position_ - target;
  target_.Normalize();
  // Define right
  Vec3 worldUp(0.f, 1.f, 0.f);
  right_ = worldUp ^ target_;
  // Define up vector
  up_ = target_ ^ right_;
  // Define view transform
  this->UpdateViewTransform();
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @name UpdateProjectionTransform
 *  @fn void UpdateProjectionTransform(const float fov,
 const float z_near,
 const float z_far,
 const float aspect);
 *  @brief  Update projection transform
 *  @param[in]  fovy    Field of view in Y axis
 *  @param[in]  z_near  New near plane
 *  @param[in]  z_fat   New far plane
 *  @param[in]  aspect  Window aspect ratio
 */
void OGLCamera::UpdateProjectionTransform(const float fovy,
                                          const float z_near,
                                          const float z_far,
                                          const float aspect) {
  assert(std::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.f);
  assert(z_near > 0.f && z_far > z_near);
  aspect_ = aspect;
  near_ = z_near;
  far_ = z_far;
  const float tanHalfFovy = std::tan(fovy / 2.f);
  projection_[0] = 1.f  / (aspect * tanHalfFovy);
  projection_[5] = 1.f  / tanHalfFovy;
  projection_[10] = - (far_ + near_) / (far_ - near_);
  projection_[11] = -1.f;
  projection_[14] = - (2.f * far_ * near_) / (far_ - near_);
  projection_[15] = 0;
}
  
/*
 *  @name OnKeyboard
 *  @fn void OnKeyboard(const OGLKey& key, const OGLKeyState& state);
 *  @brief  Handle keyboard event for camera navigation
 *  @param[in]  key   Which key trigger the event
 *  @param[in]  state State of the key (Pressed or released)
 */
void OGLCamera::OnKeyboard(const OGLKey& key, const OGLKeyState& state) {
  
}
  
  
#pragma mark -
#pragma mark Private
  
/*
 *  @name UpdateViewTransform
 *  @fn void UpdateViewTransform(void);
 *  @brief  Update view transform
 */
void OGLCamera::UpdateViewTransform(void) {
  // Define view transform
  Mat4 R, T;
  R[0] = right_.x_; R[4] = right_.y_; R[8] = right_.z_;
  R[1] = up_.x_; R[5] = up_.y_; R[9] = up_.z_;
  R[2] = target_.x_; R[6] = target_.y_; R[10] = target_.z_;
  T[12] = -position_.x_;
  T[13] = -position_.y_;
  T[14] = -position_.z_;
  view_ = R * T;
}

}  // namespace CHLib
