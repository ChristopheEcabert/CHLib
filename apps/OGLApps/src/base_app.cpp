/**
 *  @file   base_app.cpp
 *  @brief  Interface for dedicated application
 *
 *  @author Christophe Ecabert
 *  @date   15.07.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include "base_app.hpp"
#include "app_factory.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
/*
 *  @name AppProxy
 *  @fn AppProxy(void);
 *  @brief  Constructor
 */
AppProxy::AppProxy(void) {
  AppFactory::Get().Register(this);
}

/*
 *  @name AppProxy
 *  @fn AppProxy(void);
 *  @brief  Constructor
 */
AppProxy::~AppProxy(void) {}
  
}  // namespace OGLKit
