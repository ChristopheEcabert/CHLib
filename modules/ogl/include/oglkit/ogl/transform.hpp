/**
 *  @file   transform.hpp
 *  @brief  Transformation to apply on a OGLModel
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   07.08.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_TRANSFORM__
#define __OGLKIT_TRANSFORM__

#include "oglkit/core/library_export.hpp"
#include "oglkit/core/math/matrix.hpp"
#include "oglkit/core/math/quaternion.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {

/**
 *  @class  OGLTransform
 *  @brief  Transformation to apply on a OGLModel
 *  @author Christophe Ecabert
 *  @date   07.08.17
 *  @ingroup ogl
 */
template<typename T>
class OGLKIT_EXPORTS OGLTransform {
 public:
#pragma mark -
#pragma mark Type definition
  
  /** Vector */
  using Vec3 = Vector3<T>;
  /** Matrix */
  using Mat4 = Matrix4<T>;
  
#pragma mark -
#pragma mark Initialisation
  
  /**
   *  @name   OGLTransform
   *  @fn     OGLTransform(void)
   *  @brief  Constructor
   */
  OGLTransform(void);
  
  /**
   *  @name   OGLTransform
   *  @fn     OGLTransform(const OGLTransform& other)
   *  @brief  Copy constructor
   *  @param[in] other  Object to copy from
   */
  OGLTransform(const OGLTransform& other);
  
  /**
   *  @name   operator=
   *  @fn     OGLTransform& operator=(const OGLTransform& rhs)
   *  @brief  Assignment operator
   *  @param[in] rhs  Object to assign from
   *  @return Newly assigned object
   */
  OGLTransform& operator=(const OGLTransform& rhs);
  
  /**
   *  @name   OGLTransform
   *  @fn     ~OGLTransform(void) = default
   *  @brief  Destructor
   */
  ~OGLTransform(void) = default;
  
#pragma mark -
#pragma mark Usage
  
  /**
   *  @name   Update
   *  @fn     void Update(void)
   *  @brief  Update complete transform. This method should be used after 
   *          setting new parameters in order to update the overall 
   *          transformation
   */
  void Update(void);
  
#pragma mark -
#pragma mark Accessors
  
  /**
   *  @name   set_id
   *  @fn     void set_id(const size_t& id)
   *  @brief  Set ID of this transform
   *  @param[in] id ID of the transform
   */
  void set_id(const size_t& id) {
    id_ = id;
  }
  
  /**
   *  @name set_scale
   *  @fn void set_scale(const Vec3& scale)
   *  @brief  Set scaling factor. One for each direction
   *  @param[in] scale  Scale factor
   */
  void set_scale(const Vec3& scale) {
    scale_[0] = scale.x_;
    scale_[5] = scale.y_;
    scale_[10] = scale.z_;
  }
  
  /**
   *  @name set_translation
   *  @fn void set_translation(const Vec3& translation)
   *  @brief  Set object position in worl coordinate system.
   *  @param[in] translation  Object position in space (World coordinate)
   */
  void set_translation(const Vec3& translation) {
    T_[12] = -translation.x_;
    T_[13] = -translation.y_;
    T_[14] = -translation.z_;
  }
  
  /**
   *  @name   set_rotation
   *  @fn     void set_rotation(const Vec3& axis, const T angle)
   *  @brief  Set the object orientation in world coordinate system
   *  @param[in] axis   Rotation axis (quaterinion based)
   *  @param[in] angle  Amount of rotation (quaterinion based)
   */
  void set_rotation(const Vec3& axis, const T angle) {
    Quaternion<T> q(axis, angle);
    q.ToRotationMatrix(&R_);
  }

#pragma mark -
#pragma mark Private
 private:
  /** Complete transform */
  Mat4 transform_;
  /** Translation */
  Mat4 T_;
  /** Rotation */
  Mat4 R_;
  /** Scaling */
  Mat4 scale_;
  /** ID */
  size_t id_;
};
  
}  // namespace OGLKit
#endif /* __OGLKIT_TRANSFORM__ */
