/**
 *  @file   camera.cpp
 *  @brief
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

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
OGLCamera::OGLCamera(void) {
  Vector2<float> a(1.f, 2.f);
}

/*
 *  @name ~OGLCamera
 *  @fn ~OGLCamera(void)
 *  @brief  Destructor
 */
OGLCamera::~OGLCamera(void) {

}

}  // namespace CHLib
