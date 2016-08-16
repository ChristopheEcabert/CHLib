/**
 *  @file   camera.hpp
 *  @brief  OpenGL Camera abstraction class
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *    Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_OGL_CAMERA__
#define __CHLIB_OGL_CAMERA__

#include "chlib/core/library_export.hpp"
#include "chlib/core/math/vector.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {

/**
 *  @class  OGLCamera
 *  @brief  OpenGL Camera abstraction
 *  @author Christophe Ecabert
 *  @date   30/07/16
 */
class CHLIB_EXPORTS OGLCamera {

 public:

#pragma mark -
#pragma mark Initialization

  /**
   *  @name OGLCamera
   *  @fn OGLCamera(void)
   *  @brief  Constructor
   */
  OGLCamera(void);

  /**
   *  @name ~OGLCamera
   *  @fn ~OGLCamera(void)
   *  @brief  Destructor
   */
  ~OGLCamera(void);

#pragma mark -
#pragma mark Accessors

  /**
   *  @name set_position
   *  @fn void set_position(const Vector3<float>& position)
   *  @brief  Set a new camera position
   *  @param[in]  position  New camera position
   */
  void set_position(const Vector3<float>& position) {
    position_ = position;
  }

  /**
   *  @name set_target
   *  @fn void set_target(const Vector3<float>& target)
   *  @brief  Set a new target direction
   *  @param[in]  target  New targeted direction
   */
  void set_target(const Vector3<float>& target) {
    target_ = target;
  }

  /**
   *  @name set_up
   *  @fn void set_up(const Vector3<float>& up)
   *  @brief  Set a new up direction
   *  @param[in]  up  New up direction
   */
  void set_up(const Vector3<float>& up) {
    up_ = up;
  }

#pragma mark -
#pragma mark Private

 private:

  /** Camera position */
  Vector3<float> position_;
  /** Traget */
  Vector3<float> target_;
  /** Up direction */
  Vector3<float> up_;

};

}  // namespace CHLib
#endif /* _CHLIB_ogl_camera__ */
