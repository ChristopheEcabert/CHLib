/**
 *  @file   callback_wrapper.h
 *  @brief  Wrapper for OGLCallbacks interface
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16.
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface OGLCallbacksWrapper : NSObject

/** 
 *  @enum   MouseKey
 *  @brief  List of mouse btn
 */
typedef enum {
  kMouseLeftButton,
  kMouseRightButton
}MouseKey;

/**
 *  @enum   KeyState
 *  @brief  List of key state
 */
typedef enum {
  /** Key is pressed */
  kKeyPressed,
  /** Key is released */
  kKeyReleased
}KeyState;

/**
 *  @name init
 *  @fn -(id) init
 *  @brief  Constructor
 */
-(id) init;

/**
 *  @name initWithPointer
 *  @fn -(id) initWithPointer: (void*) pointer
 *  @brief  Constructor
 *  @param[in]  pointer Pointer to OGLCallbacks instance
 */
-(id) initWithPointer: (void*) pointer;

/**
 *  @name setPointer
 *  @brief  Set native callbacks
 *  @param[in]  pointer Pointer to OGLCallbacks instance
 */
-(void) setPointer:(void*) pointer;

/**
 *  @name onKeyboard
 *  @fn -(void) onKeyboard:(char) key withState:(KeyState) state
 *  @brief  Keyboard callback
 *  @param[in]  key   Value of the key that trigger the event
 *  @param[in]  state State of the key
 */
-(void) onKeyboard:(char) key withState:(KeyState) state;

/**
 *  @name onMouseMove
 *  @fn
 *  @brief  Mouse move callback
 *  @param[in]  position  Position of the cursor in the view
 */
-(void) onMouseMove: (NSPoint*) position;

/**
 *  @name onMouseClick
 *  @fn -(void) onMouseClick:(MouseKey) key 
                   withState:(KeyState)
                    state at:(NSPoint*) position
 *  @brief  Mouse click callback
 *  @param[in]  key       Which key of the mouse has triggered the event
 *  @param[in]  state     Sate of the \p key
 *  @param[in]  position  Position of the cursor in the view
 */
-(void) onMouseClick:(MouseKey) key withState:(KeyState) state at:(NSPoint*) position;

/**
 *  @name onRender
 *  @fn -(void) onRender
 *  @brief Rendering callback
 */
-(void) onRender;

/**
 *  @name onResizeWidth
 *  @fn
 *  @brief  Invoked when window change dimension
 *  @param[in]  width   New width
 *  @param[in]  hieght  New height
 */
-(void) onResizeWidth: (float)width andHeight: (float) height;

@end
