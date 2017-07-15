/**
 *  @file   ogl_view.h
 *  @brief  Custom Cocoa OpenGL view
 *
 *  @author Christophe Ecabert
 *  @date   31/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import "callback_wrapper.h"

@interface OGLView : NSOpenGLView

/**
 *  @name addCallbacks
 *  @brief  Add callback for this view
 *  @param[in]  callback  Wrapper for OGLCallbacks interface
 */
-(void) addCallbacks:(OGLCallbacksWrapper*) callback;

/**
 *  @name startLink
 *  @brief  Start rendering thread
 */
-(void) startLink;

/**
 *  @name stopLink
 *  @brief  Stop rendering thread
 */
-(void) stopLink;

@end
