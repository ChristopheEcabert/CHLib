/**
 *  @file   callback_wrapper.h
 *  @brief  Wrapper for OGLCallbacks interface
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16.
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <OpenGL/gl3.h>

#import "callback_wrapper.h"

#import "chlib/ogl/callbacks.hpp"

@interface OGLCallbacksWrapper() {
  // Callback instance
  CHLib::OGLCallbacks* callbacks_;
}
@end

@implementation OGLCallbacksWrapper

/**
 *  @name init
 *  @fn -(id) init
 *  @brief  Constructor
 */
-(id) init {
  self = [super init];
  if (self) {
    callbacks_ = nullptr;
  }
  return self;
}

/**
 *  @name initWithPointer
 *  @fn -(id) initWithPointer: (void*) pointer
 *  @brief  Constructor
 *  @param[in]  pointer Pointer to OGLCallbacks instance
 */
-(id) initWithPointer: (void*) pointer {
  self = [super init];
  if (self) {
    callbacks_ = (CHLib::OGLCallbacks*)pointer;
  }
  return self;
}

/*
 *  @name setPointer
 *  @brief  Set native callbacks
 *  @param[in]  pointer Pointer to OGLCallbacks instance
 */
-(void) setPointer:(void*) pointer {
  callbacks_ = (CHLib::OGLCallbacks*)pointer;
}

/*
 *  @name onKeyboard
 *  @fn
 *  @brief  Keyboard callback
 *  @param[in]  key   Value of the key that trigger the event
 *  @param[in]  state State of the key
 */
-(void) onKeyboard:(char) key withState:(KeyState) state {
  if (callbacks_) {
    CHLib::OGLKeyState key_state = (state == kKeyPressed ?
                                    CHLib::OGLKeyState::kPress :
                                    CHLib::OGLKeyState::kRelease);
    callbacks_->OGLKeyboardCb((CHLib::OGLKey)key, key_state);
  }
}

/*
 *  @name onMouseMove
 *  @fn
 *  @brief  Mouse move callback
 *  @param[in]  position  Position of the cursor in the view
 */
-(void) onMouseMove: (NSPoint*) position; {
  if (callbacks_) {
    callbacks_->OGLPassiveMouseCb(position->x, position->y);
  }
}

/*
 *  @name onMouseClick
 *  @fn
 *  @brief  Mouse click callback
 *  @param[in]  event Event that trigger the callback
 */
-(void) onMouseClick:(MouseKey) key
           withState:(KeyState) state
                  at:(NSPoint*) position; {
  if (callbacks_) {
    CHLib::OGLKeyState key_state = (state == kKeyPressed ?
                                    CHLib::OGLKeyState::kPress :
                                    CHLib::OGLKeyState::kRelease);
    CHLib::OGLMouse mouse = (key == kMouseLeftButton ?
                             CHLib::OGLMouse::kMouseLeft :
                             CHLib::OGLMouse::kMouseRight);
    callbacks_->OGLMouseCb(mouse, key_state, position->x, position->y);
  }
}

/*
 *  @name onRender
 *  @fn
 *  @brief Rendering callback
 */
-(void) onRender {
  glClearColor(0.f, 0.0f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (callbacks_) {
    callbacks_->OGLRenderCb();
  }
}

/*
 *  @name onResizeWidth
 *  @fn
 *  @brief  Invoked when window change dimension
 *  @param[in]  width   New width
 *  @param[in]  hieght  New height
 */
-(void) onResizeWidth: (float)width andHeight: (float) height {
  if (callbacks_) {
    callbacks_->OGLResizeCb(width, height);
  }
}

/*
 *  @name   StartRendering
 *  @fn
 *  @brief  Measure time at the begining of the rendering pass
 */
-(void) start {
  if (callbacks_) {
    callbacks_->OGLStart();
  }
}

/*
 *  @name   StopRendering
 *  @fn
 *  @brief  Stop measuring rendering time.
 */
-(void) stop {
  if (callbacks_) {
    callbacks_->OGLStop();
  }
}

@end
