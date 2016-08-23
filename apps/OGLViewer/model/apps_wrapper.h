/**
 *  @file   apps_wrapper.h
 *  @brief  Wrapper for BaseApp interface
 *
 *  @author Christophe Ecabert
 *  @date   23/08/16.
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface AppsWrapper : NSObject

#pragma mark -
#pragma mark Initialization

/**
 *  @name   initApp
 *  @brief  Initialize apps with a given configuration
 *  @param[in]  config  Path to configuration file
 */
-(id) initApp:(NSString*)app_name withConfig:(NSString*) config;

/**
 *  @name   loadApp
 *  @brief  Load an application
 *  @param[in]  config  Path to configuration file
 */
-(NSInteger) loadApp:(NSString*)app_name withConfig:(NSString*) config;

/**
 *  @name dealloc
 *  @brief  Destructor
 */
-(void) dealloc;

#pragma mark -
#pragma mark Accessors

/**
 *  @name callbacks
 *  @brief  Provide reference to OGLCallbacks
 */
-(void*) callbacks;

@end
