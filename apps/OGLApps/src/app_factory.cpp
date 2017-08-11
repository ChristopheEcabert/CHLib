/**
 *  @file   app_factory.cpp
 *  @brief  Application factory
 *  @ingroup app
 *
 *  @author Christophe Ecabert
 *  @date   15.07.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include "app_factory.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name Get
 *  @fn static AppFactory& Get(void)
 *  @brief  Provide unique instance of AppFactory
 *  @retunr AppFactory instance
 */
AppFactory& AppFactory::Get(void) {
  static AppFactory factory;
  return factory;
}
  
/*
 *  @name   AppFactory
 *  @fn     AppFactory(void)
 *  @brief  Constructor
 */
AppFactory::AppFactory(void) {}
  
/*
 *  @name   ~AppFactory
 *  @fn     ~AppFactory(void);
 *  @brief  Destructor
 */
AppFactory::~AppFactory(void) {}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @name CreateById
 *  @fn BaseApp* CreateById(const size_t id,
 const float width, const float height)
 *  @brief  Create applicaton based on a given ID
 *  @param[in]  id      Application's ID
 *  @param[in]  width   Window's width
 *  @param[in]  height  Window's height
 *  @return App instance
 */
BaseApp* AppFactory::CreateById(const size_t id,
                                const float width,
                                const float height) {
  BaseApp* app = nullptr;
  for (const auto* proxy : proxies_) {
    if (proxy->Id() == id) {
      app = proxy->Create(width, height);
      break;
    }
  }
  return app;
}

/*
 *  @name CreateById
 *  @fn BaseApp* CreateById(const std::string& name,
 const float width, const float height)
 *  @brief  Create applicaton based on a given name
 *  @param[in]  name    Application's name
 *  @param[in]  width   Window's width
 *  @param[in]  height  Window's height
 *  @return App instance
 */
BaseApp* AppFactory::CreateByName(const std::string& name,
                                  const float width,
                                  const float height) {
  BaseApp* app = nullptr;
  for (const auto* proxy : proxies_) {
    if (proxy->Name() == name) {
      app = proxy->Create(width, height);
      break;
    }
  }
  return app;
}

/*
 *  @name Register
 *  @fn void Register(const AppProxy* object)
 *  @brief  Registrer new application in the factory
 *  @param[in]  object  App's proxy to register
 */
void AppFactory::Register(const AppProxy* object) {
  // Alreay registered ?
  auto it = proxies_.find(object);
  if (it == proxies_.end()) {
    proxies_.insert(object);
  }
}
  
}  // namespace OGLKit
