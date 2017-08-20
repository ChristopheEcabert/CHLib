/**
 *  @file   tarball.hpp
 *  @brief  Helper class to handle orientation in 3D space
 *          Abstract representation of a ball
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_TARBALL__
#define __OGLKIT_TARBALL__

#include "oglkit/core/library_export.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {

/**
 *  @struct OGLTarball
 *  @brief  Helper class to handle orientation in 3D space
 *          Uses right hand coordinate system
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  @ingroup ogl
 */
template<typename T>
struct OGLKIT_EXPORTS OGLTarball {

  /**
   *  @name   OGLTarball
   *  @fn     OGLTarball(void)
   *  @brief  Constructor
   */
  OGLTarball(void) {

  }

  /**
   *  @name   OGLTarball
   *  @fn     OGLTarball(const OGLTarball& other)
   *  @brief  Copy constructor
   *  @param[in]  other Object to copy from
   */
  OGLTarball(const OGLTarball& other) {
    v_angle = other.v_angle;
    h_angle = other.h_angle;
  }

  /**
   *  @name operator=
   *  @fn OGLTarball& operator=(const OGLTarball& rhs)
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return   New assigned object
   */
  OGLTarball& operator=(const OGLTarball& rhs) {
    if (this != &rhs) {

    }
    return *this;
  }

  /**
   *  @name   OGLTarball
   *  @fn     ~OGLTarball(void)
   *  @brief  Destructor
   */
  ~OGLTarball(void) {

  }

  /**
   *  @name UpdateOrientation
   *  @fn void UpdateOrientation(const T delta_x, const T delta_y)
   *  @brief  Update vertical and horizontal angles for a given \p delta_x 
   *          and \p delta_y screen displacement.
   *  @param[in]  delta_x   Screen variation in X direction
   *  @param[in]  delta_y   Screen variation in Y direction
   */
  void UpdateOrientation(const T delta_x, const T delta_y) {

  }

  /** Vertical angle - Along X axis */
  T v_angle;
  /** Horizontal angle - Along Y axis */
  T h_angle;
};

}  // namespace OGLKit


#endif /* __OGLKIT_TARBALL__ */
