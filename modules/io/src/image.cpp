/**
 *  @file   image.cpp
 *  @brief  Image object registration mechanism
 *
 *  @author Christophe Ecabert
 *  @date   15.07.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include "oglkit/io/image.hpp"
#include "oglkit/io/image_factory.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
/*
 *  @name   ImageProxy
 *  @fn     ImageProxy(void)
 *  @brief  Constructor
 */
ImageProxy::ImageProxy(void) {
  ImageFactory::Get().Register(this);
}
  
/*
 *  @name   ~ImageProxy
 *  @fn     ~ImageProxy(void)
 *  @brief  Destructor
 */
ImageProxy::~ImageProxy(void) {}
  
}  // namespace OGLKit
