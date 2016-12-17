/**
 *  @file   camera.hpp
 *  @brief  OpenGL Camera abstraction
 *          Based on : http://learnopengl.com/#!Getting-started/Camera
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_OGL_CAMERA__
#define __CHLIB_OGL_CAMERA__

#include "chlib/core/library_export.hpp"
#include "chlib/core/math/vector.hpp"
#include "chlib/core/math/matrix.hpp"
#include "chlib/ogl/key_types.hpp"

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
#pragma mark Type defintion
  
  /** Vector type */
  using Vec3 = Vector3<float>;
  /** Matrix type */
  using Mat4 = Matrix4<float>;

#pragma mark -
#pragma mark Initialization

  /**
   *  @name OGLCamera
   *  @fn OGLCamera(void)
   *  @brief  Constructor
   */
  OGLCamera(void);
  
  /**
   *  @name OGLCamera
   *  @fn OGLCamera(void)
   *  @brief  Constructor
   *  @param[in]  position  Where to place the camera
   *  @param[in]  target    Where to point at
   */
  OGLCamera(const Vec3& position, const Vec3& target);
  
  /**
   *  @name OGLCamera
   *  @fn OGLCamera(const OGLCamera& other)
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy from
   */
  OGLCamera(const OGLCamera& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLCamera& operator=(const OGLCamera& rhs)
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  OGLCamera& operator=(const OGLCamera& rhs) = delete;

  /**
   *  @name ~OGLCamera
   *  @fn ~OGLCamera(void)
   *  @brief  Destructor
   */
  ~OGLCamera(void);
  
  /**
   *  @name LookAt
   *  @fn void LookAt(const Vec3& position, const Vec3& target);
   *  @brief  Define view transformation
   *  @param[in]  position  Where to place the camera
   *  @param[in]  target    Where to point at
   */
  void LookAt(const Vec3& position, const Vec3& target);
  
#pragma mark -
#pragma mark Usage

  /**
   *  @name UpdateProjectionTransform
   *  @fn void UpdateProjectionTransform(const float fov, 
                                         const float z_near,
                                         const float z_far,
                                         const float aspect);
   *  @brief  Update projection transform
   *  @param[in]  fov     Field of view in Y axis
   *  @param[in]  z_near  New near plane
   *  @param[in]  z_fat   New far plane
   *  @param[in]  aspect  Window aspect ratio
   */
  void UpdateProjectionTransform(const float fovy,
                                 const float z_near,
                                 const float z_far,
                                 const float aspect);
  
  /**
   *  @name UpdateProjectionTransform
   *  @fn void UpdateProjectionTransform();
   *  @brief  Update projection transform
   */
  void UpdateProjectionTransform(void);
  
  /**
   *  @name OnKeyboard
   *  @fn void OnKeyboard(const OGLKey& key, const OGLKeyState& state);
   *  @brief  Handle keyboard event for camera navigation
   *  @param[in]  key   Which key trigger the event
   *  @param[in]  state State of the key (Pressed or released)
   */
  void OnKeyboard(const OGLKey& key, const OGLKeyState& state);
  
  /**
   *  @name
   *  @fn
   *  @brief  Handle click event for camera object
   *  @param[in]  button  Which button has triggered the event
   *  @param[in]  state   Button's state
   *  @param[in]  x       X Position in the view
   *  @param[in]  y       Y Position in the view
   */
  void OnMouseClick(const OGLMouse& button,
                    const OGLKeyState& state,
                    const int x,
                    const int y);
  
  /**
   * @name  OnMouseMove
   * @fn    void OnMouseMove(const int x, const int y)
   * @brief Method to invoke when mouse moves on the screen
   * @param x   Current cursor X position
   * @param y   Current cursor Y position
   */
  void OnMouseMove(const int x, const int y);

#pragma mark -
#pragma mark Accessors
  
  /**
   *  @name set_window_dimension
   *  @fn void set_window_dimension(const float width, const float height)
   *  @brief  Set window dimension
   *  @param[in]  width   View's width
   *  @param[in]  height  View's height
   */
  void set_window_dimension(const float width, const float height) {
    win_width_ = width;
    win_height_ = height;
    fov_ = win_width_ / win_height_;
  }

  /**
   *  @name get_position
   *  @fn const Vec3 get_position(void) const
   *  @brief  Get camera position
   */
  const Vec3 get_position(void) const {
    return position_;
  }
  
  /**
   *  @name get_view
   *  @fn const Mat4 get_view(void) const
   *  @brief  Get view transformation
   */
  const Mat4 get_view(void) const {
    return view_;
  }
  
  /**
   *  @name get_projection
   *  @fn const Mat4 get_projection(void) const
   *  @brief  Get projection transformation
   */
  const Mat4 get_projection(void) const {
    return projection_;
  }
  
  /**
   *  @name get_transform
   *  @fn const Mat4 get_transform(void) const
   *  @brief  Get full camera transformation
   */
  const Mat4 get_transform(void) const {
    return projection_ * view_;
  }

#pragma mark -
#pragma mark Private

 private:
  
  /**
   * @enum  CameraState
   * @brief List all possible state in the trackball state machine
   */
  enum CameraState {
    /** Nothing currently happening */
    kNone,
    /** Doing rotation */
    kRotate
  };
  
  /**
   *  @name UpdateViewTransform
   *  @fn void UpdateViewTransform(void);
   *  @brief  Update view transform
   */
  void UpdateViewTransform(void);
  
  /**
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
  void GetMouseProjectionOnBall(const int x,
                                const int y,
                                Vector3<float>* pts);

  /** Camera position */
  Vec3 position_;
  /** Target */
  Vec3 target_;
  /** Up direction */
  Vec3 up_;
  /** Right */
  Vec3 right_;
  /** Window aspect ratio */
  float aspect_;
  /** Near plane */
  float near_;
  /** Far plane */
  float far_;
  /** Field of view */
  float fov_;
  /** View transformation */
  Mat4 view_;
  /** Projection transform */
  Mat4 projection_;
  /** Window width */
  float win_width_;
  /** Window hieght */
  float win_height_;
  /** State machine */
  CameraState state_;
  /** Displacement speed */
  float move_speed_;
  /** Rotation speed */
  float rotation_speed_;
  /** Rotation starting position */
  Vector3<float> rotations_start_;
  /** Rotation end position */
  Vector3<float> rotations_end_;

};

}  // namespace CHLib
#endif /* _CHLIB_ogl_camera__ */
