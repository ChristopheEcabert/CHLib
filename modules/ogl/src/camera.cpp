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
#include "chlib/core/math/quaternion.hpp"

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
                              fov_(M_PI/6.f),
                              state_(kNone),
                              move_speed_(0.002f),
                              rotation_speed_(1.f),
                              rotations_start_(0.f, 0.f, 0.f),
                              rotations_end_(0.f, 0.f, 0.f) {
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
  fov_(M_PI/6.f),
  state_(kNone),
  move_speed_(5.f),
  rotation_speed_(1.f),
  rotations_start_(0.f, 0.f, 0.f),
  rotations_end_(0.f, 0.f, 0.f) {
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
 *  @name UpdateProjectionTransform
 *  @fn void UpdateProjectionTransform(void);
 *  @brief  Update projection transform
 */
void OGLCamera::UpdateProjectionTransform(void) {
  const float tanHalfFovy = std::tan(fov_ / 2.f);
  projection_[0] = 1.f  / (aspect_ * tanHalfFovy);
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
 *  @param[in]  dt    Delta time between each rendering pass
 */
void OGLCamera::OnKeyboard(const OGLKey& key,
                           const OGLKeyState& state,
                           const float dt) {
  // Action based on key
  switch (key) {
    case OGLKey::kw : position_ -= target_ * move_speed_ * dt;
      this->UpdateViewTransform();
      break;
      
    case OGLKey::ks : position_ += target_ * move_speed_ * dt;
      this->UpdateViewTransform();
      break;
      
    case OGLKey::kd : position_ += right_ * move_speed_;
      this->UpdateViewTransform();
      break;
      
    case OGLKey::ka : position_ -= right_ * move_speed_;
      this->UpdateViewTransform();
      break;
      
    default:
      break;
  }
}
  
/*
 *  @name
 *  @fn
 *  @brief  Handle click event for camera object
 *  @param[in]  button  Which button has triggered the event
 *  @param[in]  state   Button's state
 *  @param[in]  x       X Position in the view
 *  @param[in]  y       Y Position in the view
 */
void OGLCamera::OnMouseClick(const OGLMouse& button,
                             const OGLKeyState& state,
                             const int x,
                             const int y) {
  if (state != OGLKeyState::kPress) {
    state_ = CameraState::kNone;
  } else {
    state_ = CameraState::kRotate;
    // Get projection onto ball
    this->GetMouseProjectionOnBall(x, y, &rotations_start_);
    rotations_end_ = rotations_start_;
  }
}
  
/*
 * @name  OnMouseMove
 * @fn    void OnMouseMove(const int x, const int y)
 * @brief Method to invoke when mouse moves on the screen
 * @param x   Current cursor X position
 * @param y   Current cursor Y position
 */
void OGLCamera::OnMouseMove(const int x, const int y) {
  if (state_ == CameraState::kRotate) {
    // Should update transformation
    // Get new projection
    this->GetMouseProjectionOnBall(x, y, &rotations_end_);
    // update transform, compute axis + angle
    float angle = std::acos(rotations_start_ * rotations_end_);
    if (!std::isnan(angle) && angle != 0.f) {
      angle *= rotation_speed_;
      Vector3<float> axis = rotations_start_ ^ rotations_end_;
      if (axis.x_ != 0.f || axis.y_ != 0.f || axis.z_ != 0.f) {
        // Save position
        rotations_start_ = rotations_end_;
        // Setup quaternion
        Quaternion<float> quat(axis, -angle);
        quat.Normalize();
        // Get transformation
        Matrix3<float> rot;
        quat.ToRotationMatrix(&rot);
        // Update camera orientation
        target_ = rot * target_;
        right_ = rot * right_;
        up_ = rot * up_;
        position_ = rot * position_;
        this->UpdateViewTransform();
      }
    }
  }
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
  
/*
 * @name  GetMouseProjectionOnBall
 * @fn void GetMouseProjectionOnBall(const int x,
                                     const int y,
                                     Vector3<float>3* pts)
 * @brief Project screen loation onto ball
 * @param[in] x       Cursor X position on the screen
 * @param[in] y       Cursor Y position on the screen
 * @param[out] pts    Corresponding points on sphere
 * @see https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
 */
void OGLCamera::GetMouseProjectionOnBall(const int x,
                                         const int y,
                                         Vector3<float>* pts) {
  // Convert screen coordinate into [-1, 1] range,
  pts->x_ = ((2.f * x) / win_width_) - 1.f;
  pts->y_ = 1.f - ((2.f * y) / win_height_);
  pts->z_ = 0.f;
  // Compute distance from O -> Pts
  float norm = pts->x_ * pts->x_ + pts->y_ * pts->y_;
  if (norm <= 1.f) {
    // pythagore
    pts->z_ = std::sqrt(1.f - norm);
  } else {
    // Nearest points
    pts->Normalize();
  }
}

}  // namespace CHLib
