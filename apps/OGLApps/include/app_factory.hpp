/**
 *  @file   app_factory.hpp
 *  @brief  Application factory
 *  @ingroup app
 *
 *  @author Christophe Ecabert
 *  @date   15.07.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_APP_FACOTRY__
#define __CHLIB_APP_FACOTRY__

#include <unordered_set>

#include "base_app.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class AppFactory
 *  @brief  Singleton generator with registration mechnism to add more apps
 *  @author Christophe Ecabert
 *  @date 15.07.2017
 *  @ingroup app
 */
class AppFactory {
 public:
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name Get
   *  @fn static AppFactory& Get(void)
   *  @brief  Provide unique instance of AppFactory
   *  @retunr AppFactory instance
   */
  static AppFactory& Get(void);
  
  /**
   *  @name   AppFactory
   *  @fn     AppFactory(const AppFactory& other) = delete;
   *  @brief  Copy Constructor
   */
  AppFactory(const AppFactory& other) = delete;
  
  /**
   *  @name   operator=
   *  @fn     AppFactory& operator=(const AppFactory& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned operator
   */
  AppFactory& operator=(const AppFactory& rhs) = delete;
  
  /**
   *  @name   ~AppFactory
   *  @fn     ~AppFactory(void);
   *  @brief  Destructor
   */
  ~AppFactory(void);
  
#pragma mark -
#pragma mark Usage
  
  /**
   *  @name CreateById
   *  @fn BaseApp* CreateById(const size_t id, 
                              const float width, const float height)
   *  @brief  Create applicaton based on a given ID
   *  @param[in]  id      Application's ID
   *  @param[in]  width   Window's width
   *  @param[in]  height  Window's height
   *  @return App instance or nullptr if ID is unknown
   */
  BaseApp* CreateById(const size_t id, const float width, const float height);
  
  /**
   *  @name CreateById
   *  @fn BaseApp* CreateById(const std::string& name,
                              const float width, const float height)
   *  @brief  Create applicaton based on a given name
   *  @param[in]  name    Application's name
   *  @param[in]  width   Window's width
   *  @param[in]  height  Window's height
   *  @return App instance or nullptr if name is unknown
   */
  BaseApp* CreateByName(const std::string& name,
                        const float width,
                        const float height);
  
  /**
   *  @name Register
   *  @fn void Register(const AppProxy* object)
   *  @brief  Registrer new application in the factory
   *  @param[in]  object  App's proxy to register
   */
  void Register(const AppProxy* object);
  
#pragma mark -
#pragma mark Private
 private:
  
  /**
   *  @name   AppFactory
   *  @fn     AppFactory(void)
   *  @brief  Constructor
   */
  AppFactory(void);
  
  /** Application proxies */
  std::unordered_set<const AppProxy*> proxies_;
};
}  // namespace CHLib
#endif /* __CHLIB_APP_FACOTRY__ */
