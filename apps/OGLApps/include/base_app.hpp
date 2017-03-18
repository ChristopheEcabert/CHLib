/**
 *  @file   base_app.hpp
 *  @brief
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_BASE_APP__
#define __CHLIB_BASE_APP__

#include <string>

#include "chlib/ogl/callbacks.hpp"
#include "chlib/ogl/ogl_mesh.hpp"
#include "chlib/ogl/camera.hpp"
#include "chlib/ogl/shader.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  BaseApp
 *  @brief  Application interface
 *  @author Christophe Ecabert
 *  @date   23/08/16
 */
class BaseApp : public OGLCallbacks {
 public:
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name Load
   *  @fn virtual int Load(const std::string& config) = 0
   *  @brief  Initialize application (i.e. Scene)
   *  @param[in]  config  Path to the scene configuration file
   *  @return -1 if error, 0 otherwise
   */
  virtual int Load(const std::string& config) = 0;
};
}  // namespace CHLib
#endif /* __CHLIB_BASE_APP__ */
