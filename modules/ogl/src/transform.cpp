/**
 *  @file   transform.cpp
 *  @brief  Transformation to apply on a OGLModel
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   07.08.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include "oglkit/ogl/transform.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Initialisation
  
/*
 *  @name   OGLTransform
 *  @fn     OGLTransform(void)
 *  @brief  Constructor
 */
template<typename T>
OGLTransform<T>::OGLTransform(void) {
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @name   Update
 *  @fn     void Update(void)
 *  @brief  Update complete transform. This method should be used after
 *          setting new parameters in order to update the overall
 *          transformation
 */
template<typename T>
void OGLTransform<T>::Update(void) {
  
}
  
  
#pragma mark -
#pragma mark Explicit instantiation
  
/** Float Transform */
template class OGLTransform<float>;
/** Double Transform */
template class OGLTransform<double>;
  
}  // namespace OGLKit
