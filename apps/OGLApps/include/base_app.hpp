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
   *  @name BaseApp
   *  @fn BaseApp(const float win_width, const float win_height)
   *  @brief  Basic constructor
   *  @param[in]  win_width   View's width
   *  @param[in]  win_height  View's height
   */
  BaseApp(const float win_width, const float win_height) :
    win_width_(win_width),
    win_height_(win_height) {
  }
  
  /**
   *  @name ~BaseApp
   *  @fn virtual ~BaseApp(void)
   *  @brief  Destructor
   */
  virtual ~BaseApp(void) {}
  
  /**
   *  @name Load
   *  @fn virtual int Load(const std::string& config) = 0
   *  @brief  Initialize application (i.e. Scene)
   *  @param[in]  config  Path to the scene configuration file
   *  @return -1 if error, 0 otherwise
   */
  virtual int Load(const std::string& config) = 0;
  
#pragma mark -
#pragma mark Protected
 protected:
  /** Window dimension - width */
  float win_width_;
  /** Window dimension - hieght */
  float win_height_;
  
};
}  // namespace CHLib
#endif /* __CHLIB_BASE_APP__ */
