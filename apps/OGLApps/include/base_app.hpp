/**
 *  @file   base_app.hpp
 *  @brief  Interface for dedicated application
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
 *  @ingroup app
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
  
/**
 *  @class  AppProxy
 *  @brief  Registration mechanism for application
 *  @author Christophe Ecabert
 *  @date   15.07.17
 *  @ingroup app
 */
class AppProxy {
 public:
  
  /**
   *  @name AppProxy
   *  @fn AppProxy(void);
   *  @brief  Constructor
   */
  AppProxy(void);
  
  /**
   *  @name AppProxy
   *  @fn AppProxy(void);
   *  @brief  Constructor
   */
  virtual ~AppProxy(void);
  
  /**
   *  @name Create
   *  @fn virtual BaseApp* Create(const float width, const float height) const = 0
   *  @brief  Create an app of a given type
   *  @param[in]  width Window's width    Window's width
   *  @param[in]  height Window's height  Window's height
   */
  virtual BaseApp* Create(const float width, const float height) const = 0;
  
  /**
   *  @name Id
   *  @fn virtual size_t Id(void) const = 0
   *  @brief  Provide ID of the app
   *  @return App's ID
   */
  virtual size_t Id(void) const = 0;
  
  /**
   *  @name Name
   *  @fn virtual const char* Name(void) const = 0
   *  @brief  Provide Name of the app
   *  @return App's name
   */
  virtual const char* Name(void) const = 0;
};
  
}  // namespace CHLib
#endif /* __CHLIB_BASE_APP__ */
