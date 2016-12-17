/**
 *  @file   app01.hpp
 *  @brief  Basic lighting
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_APP01__
#define __CHLIB_APP01__

#include "base_app.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  App01
 *  @brief  Debug class
 *  @author Christophe Ecabert
 *  @date   23/08/16
 */
class App01 : public BaseApp {
 public:
 
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name App01
   *  @fn App01(void)
   *  @brief  Constructor
   *  @param[in]  win_width   View's width
   *  @param[in]  win_height  View's height
   */
  App01(const float win_width, const float win_height);
  
  /**
   *  @name App01
   *  @fn App01(const App01& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy from
   */
  App01(const App01& other) = delete;
  
  /**
   *  @name operator=
   *  @fn App01& operator=(const App01& rhs) = delete;
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  App01& operator=(const App01& rhs) = delete;
  
  /**
   *  @name ~App01
   *  @fn ~App01(void)
   *  @brief  Destructor
   */
  ~App01(void);
  
  /**
   *  @name Load
   *  @fn int Load(const std::string& config) = 0
   *  @brief  Initialize application (i.e. Scene)
   *  @param[in]  config  Path to the scene configuration file
   *  @return -1 if error, 0 otherwise
   */
  int Load(const std::string& config);
  
#pragma mark -
#pragma mark Callbacks
  
  /**
   * @name  OGLKeyboardCb
   * @fn  void OGLKeyboardCb(const OGLKey& key,
   *                                 const OGLKeyState& state)
   * @brief Callback for keyboard event
   * @param[in] key     Key that trigger the callback
   * @param[in] state   Key state at that time
   */
  void OGLKeyboardCb(const OGLKey& key, const OGLKeyState& state);
  
  /**
   * @name  OGLRenderCb
   * @fn  void OGLRenderCb(void)
   * @brief Callback invoked when scene need to be rendered
   */
  void OGLRenderCb(void);
};
}  // namespace CHLib
#endif /* __CHLIB_APP01__ */
