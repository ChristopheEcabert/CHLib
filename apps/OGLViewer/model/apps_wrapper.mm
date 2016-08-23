/**
 *  @file   apps_wrapper.mm
 *  @brief  Wrapper for BaseApp interface
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16.
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import "apps_wrapper.h"

#import "base_app.hpp"
#import "apps.hpp"

@interface AppsWrapper() {
  /** Application pointer */
  CHLib::BaseApp* app_;
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
-(id) initApp:(NSString*)app_name withConfig:(NSString*) config {
  self = [super init];
  if (self) {
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
  const char* name = [app_name UTF8String];
  if (strncmp(name, "Debug", 5) == 0) {
    app_ = new CHLib::App00();
    err = app_->Load(std::string([config UTF8String]));
  } else if (strncmp(name, "Basic Lighting", 5) == 0) {
    app_ = new CHLib::App01();
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
