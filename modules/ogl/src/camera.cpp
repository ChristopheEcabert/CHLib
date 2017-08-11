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

#include "oglkit/ogl/camera.hpp"
#include "oglkit/core/math/vector.hpp"
#include "oglkit/core/math/matrix.hpp"
#include "oglkit/core/math/quaternion.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {

#pragma mark -
#pragma mark Initialization

/*
 *  @name OGLCamera
 *  @fn OGLCamera(void)
 *  @brief  Constructor
 */
template<typename T>
OGLCamera<T>::OGLCamera(void) :  position_(0.0, 0.0, 1.0),
                                 target_(0.0, 0.0, 0.0),
                                 aspect_(1.25f),
                                 near_(0.01f),
                                 far_(100.0),
                                 fov_(M_PI/6.0),
                                 state_(kNone),
                                 move_speed_(0.002f),
                                 rotation_speed_(1.0),
                                 rotations_start_(0.0, 0.0, 0.0),
                                 rotations_end_(0.0, 0.0, 0.0) {
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
template<typename T>
OGLCamera<T>::OGLCamera(const Vec3& position, const Vec3& target) :
  position_(position),
  target_(target),
  aspect_(1.25f),
  near_(0.01f),
  far_(1000.0),
  fov_(M_PI/6.0),
  state_(kNone),
  move_speed_(5.0),
  rotation_speed_(1.0),
  rotations_start_(0.0, 0.0, 0.0),
  rotations_end_(0.0, 0.0, 0.0) {
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
template<typename T>
OGLCamera<T>::~OGLCamera(void) {
}
  
/*
 *  @name LookAt
 *  @fn void LookAt(const Vec3& position, const Vec3& target);
 *  @brief  Define view transformation
 *  @param[in]  position  Where to place the camera
 *  @param[in]  target    Where to point at
 */
template<typename T>
void OGLCamera<T>::LookAt(const Vec3& position, const Vec3& target) {
  // Define target direction
  position_ = position;
  target_ = position_ - target;
  target_.Normalize();
  // Define right
  Vec3 worldUp(0.0, 1.0, 0.0);
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
 *  @fn void UpdateProjectionTransform(const T fov,
                                       const T z_near,
                                       const T z_far,
                                       const T aspect);
 *  @brief  Update projection transform
 *  @param[in]  fovy    Field of view in Y axis
 *  @param[in]  z_near  New near plane
 *  @param[in]  z_fat   New far plane
 *  @param[in]  aspect  Window aspect ratio
 */
template<typename T>
void OGLCamera<T>::UpdateProjectionTransform(const T fovy,
                                             const T z_near,
                                             const T z_far,
                                             const T aspect) {
  assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > 0.0);
  assert(z_near > 0.0 && z_far > z_near);
  aspect_ = aspect;
  near_ = z_near;
  far_ = z_far;
  const T tanHalfFovy = std::tan(fovy / 2.0);
  projection_[0] = 1.0  / (aspect * tanHalfFovy);
  projection_[5] = 1.0  / tanHalfFovy;
  projection_[10] = - (far_ + near_) / (far_ - near_);
  projection_[11] = -1.0;
  projection_[14] = - (2.0 * far_ * near_) / (far_ - near_);
  projection_[15] = 0;
}
  
/*
 *  @name UpdateProjectionTransform
 *  @fn void UpdateProjectionTransform(void);
 *  @brief  Update projection transform
 */
template<typename T>
void OGLCamera<T>::UpdateProjectionTransform(void) {
  const T tanHalfFovy = std::tan(fov_ / 2.0);
  projection_[0] = 1.0  / (aspect_ * tanHalfFovy);
  projection_[5] = 1.0  / tanHalfFovy;
  projection_[10] = - (far_ + near_) / (far_ - near_);
  projection_[11] = -1.0;
  projection_[14] = - (2.0 * far_ * near_) / (far_ - near_);
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
template<typename T>
void OGLCamera<T>::OnKeyboard(const OGLKey& key,
                              const OGLKeyState& state,
                              const T dt) {
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
template<typename T>
void OGLCamera<T>::OnMouseClick(const OGLMouse& button,
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
template<typename T>
void OGLCamera<T>::OnMouseMove(const int x, const int y) {
  if (state_ == CameraState::kRotate) {
    // Should update transformation
    // Get new projection
    this->GetMouseProjectionOnBall(x, y, &rotations_end_);
    // update transform, compute axis + angle
    T angle = std::acos(rotations_start_ * rotations_end_);
    if (!std::isnan(angle) && angle != 0.0) {
      angle *= rotation_speed_;
      Vector3<T> axis = rotations_start_ ^ rotations_end_;
      if (axis.x_ != 0.0 || axis.y_ != 0.0 || axis.z_ != 0.0) {
        // Save position
        rotations_start_ = rotations_end_;
        // Setup quaternion
        Quaternion<T> quat(axis, -angle);
        quat.Normalize();
        // Get transformation
        Matrix3<T> rot;
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
template<typename T>
void OGLCamera<T>::UpdateViewTransform(void) {
  // Define view transform
  Mat4 R, Tx;
  R[0] = right_.x_; R[4] = right_.y_; R[8] = right_.z_;
  R[1] = up_.x_; R[5] = up_.y_; R[9] = up_.z_;
  R[2] = target_.x_; R[6] = target_.y_; R[10] = target_.z_;
  Tx[12] = -position_.x_;
  Tx[13] = -position_.y_;
  Tx[14] = -position_.z_;
  view_ = R * Tx;
}
  
/*
 * @name  GetMouseProjectionOnBall
 * @fn void GetMouseProjectionOnBall(const int x,
                                     const int y,
                                     Vector3<T>3* pts)
 * @brief Project screen loation onto ball
 * @param[in] x       Cursor X position on the screen
 * @param[in] y       Cursor Y position on the screen
 * @param[out] pts    Corresponding points on sphere
 * @see https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
 */
template<typename T>
void OGLCamera<T>::GetMouseProjectionOnBall(const int x,
                                            const int y,
                                            Vector3<T>* pts) {
  // Convert screen coordinate into [-1, 1] range,
  pts->x_ = ((2.0 * x) / win_width_) - 1.0;
  pts->y_ = 1.0 - ((2.0 * y) / win_height_);
  pts->z_ = 0.0;
  // Compute distance from O -> Pts
  T norm = pts->x_ * pts->x_ + pts->y_ * pts->y_;
  if (norm <= 1.0) {
    // pythagore
    pts->z_ = std::sqrt(1.0 - norm);
  } else {
    // Nearest points
    pts->Normalize();
  }
}
  
#pragma mark -
#pragma mark Explicit instantiation
  
/** Float Camera */
template class OGLCamera<float>;
/** double Camera */
template class OGLCamera<double>;
  
}  // namespace OGLKit
