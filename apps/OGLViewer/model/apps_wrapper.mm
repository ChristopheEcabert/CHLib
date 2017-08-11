/**
 *  @file   apps_wrapper.mm
 *  @brief  Wrapper for BaseApp interface
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16.
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import "apps_wrapper.h"

#include "oglkit/ogl/texture_manager.hpp"

#include "base_app.hpp"
#include "app_factory.hpp"

@interface AppsWrapper() {
  /** Application pointer */
  OGLKit::BaseApp* app_;
  /** View width */
  float width_;
  /** View height */
  float height_;
}

@end

@implementation AppsWrapper

#pragma mark -
#pragma mark Initialization

/*
 *  @name   initApp
 *  @brief  Initialize apps with a given configuration
 *  @param[in]  config  Path to configuration file
 */
-(id) initApp:(NSString*)app_name withConfig:(NSString*) config withSize:(NSSize)size {
  self = [super init];
  if (self) {
    // Release already loaded texture
    OGLKit::OGLTextureManager::Instance().Remove("");
    // Load new app
    width_ = size.width;
    height_ = size.height;
    [self loadApp:app_name withConfig:config];
  }
  return self;
}

/*
 *  @name   loadApp
 *  @brief  Load an application
 *  @param[in]  config  Path to configuration file
 */
-(NSInteger) loadApp:(NSString*)app_name withConfig:(NSString*) config {
  // If app already loaded, release if
  NSInteger err = -1;
  if (app_) {
    delete app_;
  }
  // Load proper app
  std::string name([app_name UTF8String]);
  app_ = OGLKit::AppFactory::Get().CreateByName(name, width_, height_);
  if (app_) {
    err = app_->Load(std::string([config UTF8String]));
  }
  return err;
}

/*
 *  @name dealloc
 *  @brief  Destructor
 */
-(void) dealloc {
  // Release app
  if (app_) {
    delete app_;
  }
}

#pragma mark -
#pragma mark Accessors

/*
 *  @name callbacks
 *  @brief  Provide reference to OGLCallbacks
 */
-(void*) callbacks {
  return (void*)app_;
}

@end
