/**
 *  @file   ogl_view.mm
 *  @brief  Custom Cocoa OpenGL view
 *
 *  @author Christophe Ecabert
 *  @date   31/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <OpenGL/gl3.h>

#import "ogl_view.h"
#import "callback_wrapper.h"

@interface OGLView() {
  /** OGL Callback wrapper */
  OGLCallbacksWrapper* callback_;
}
@end

@implementation OGLView

#pragma mark -
#pragma mark OpenGL Event

/**
 *  @name awakeFromNib
 *  @fn -(void) awakeFromNib
 *  @brief  Mehtod invoked when Nib file is loaded
 */
-(void) awakeFromNib {
  // Init callbacks
  callback_ = nil;
  // Init tracking area
  NSTrackingAreaOptions opt = (NSTrackingActiveAlways |
                               NSTrackingInVisibleRect |
                               NSTrackingMouseMoved);
  NSTrackingArea* area = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                      options:opt owner:self
                                                     userInfo:nil];
  [self addTrackingArea:area];
  // Create OGL pixel format attribute
  NSOpenGLPixelFormatAttribute attribs[] = {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAColorSize, 24,
    NSOpenGLPFAAlphaSize, 8,
    NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFANoRecovery,
    0
  };
  // Create pixel format
  NSOpenGLPixelFormat* frmt = [[NSOpenGLPixelFormat alloc]
                               initWithAttributes:attribs];
  if (frmt) {
    // Set pixel format for the view
    [self setPixelFormat:frmt];
    // Create context
    NSOpenGLContext* ctx = [[NSOpenGLContext alloc]
                            initWithFormat:frmt shareContext:nil];
    [self setOpenGLContext:ctx];
    // Set context as current
    [[self openGLContext] makeCurrentContext];
  }
}

-(void) drawRect:(NSRect)dirtyRect {
  [super drawRect:dirtyRect];
  // If callback callit, otherwise, render black scquare
  if (callback_) {
    [callback_ onRender];
  } else {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

  }
  // Swap buffer
  [[self openGLContext] flushBuffer];
}

#pragma mark -
#pragma mark Mouse Event

-(BOOL) acceptsFirstResponder {
  return YES;
}

/**
 *  @name mouseDown
 *  @brief  Function invoked when left mouse is hit
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) mouseDown:(NSEvent *)theEvent {
  if ([theEvent type] == NSLeftMouseDown && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseClick: kMouseLeftButton withState:kKeyPressed at:&pos];
  } else {
    [super mouseDown:theEvent];
  }
}

/**
 *  @name mouseDown
 *  @brief  Function invoked when left mouse is hit
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) mouseUp:(NSEvent *)theEvent {
  if ([theEvent type] == NSLeftMouseUp && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseClick: kMouseLeftButton withState:kKeyReleased at:&pos];
  } else {
    [super mouseUp:theEvent];
  }
}

/**
 *  @name rightMouseDown
 *  @brief  Function invoked when right mouse is hit
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) rightMouseDown:(NSEvent *)theEvent {
  if ([theEvent type] == NSRightMouseDown && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseClick: kMouseRightButton withState:kKeyPressed at:&pos];
  } else {
    [super rightMouseDown:theEvent];
  }
}

/**
 *  @name rightMouseDown
 *  @brief  Function invoked when right mouse is hit
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) rightMouseUp:(NSEvent *)theEvent {
  if ([theEvent type] == NSRightMouseUp && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseClick: kMouseRightButton withState:kKeyReleased at:&pos];
  } else {
    [super rightMouseUp:theEvent];
  }
}

/**
 *  @name mouseMoved
 *  @brief  Function invoked when left mouse moved
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void)mouseMoved:(NSEvent *)theEvent {
  if ([theEvent type] == NSMouseMoved && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseMove:&pos];
  } else {
    [super mouseMoved:theEvent];
  }
}

/**
 *  @name mouseDragged
 *  @brief  Update position when mouse left is dragged
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) mouseDragged:(NSEvent *)theEvent {
  if ([theEvent type] == NSLeftMouseDragged && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseClick: kMouseLeftButton withState:kKeyPressed at:&pos];
  } else {
    [super mouseDragged:theEvent];
  }
}

/**
 *  @name mouseDragged
 *  @brief  Update position when mouse left is dragged
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) rightMouseDragged:(NSEvent *)theEvent {
  if ([theEvent type] == NSRightMouseDragged && callback_) {
    NSPoint pos = [self convertPoint: [theEvent locationInWindow] fromView:nil];
    [callback_ onMouseClick: kMouseRightButton withState:kKeyPressed at:&pos];
  } else {
    [super rightMouseDragged:theEvent];
  }
}

#pragma mark -
#pragma mark Keyboard Event

/**
 *  @name keyDown
 *  @brief  Callback invoked when a key is pressed
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) keyDown:(NSEvent *)theEvent {
  if ([theEvent type] == NSKeyDown && callback_) {
    char ch = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
    [callback_ onKeyboard:ch withState:kKeyPressed];
  } else {
    [super keyDown:theEvent];
  }
}

/**
 *  @name keyDown
 *  @brief  Callback invoked when a key is pressed
 *  @param[in]  theEvent  Event that trigger callback
 */
-(void) keyUp:(NSEvent *)theEvent {
  if ([theEvent type] == NSKeyUp && callback_) {
    char ch = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
    [callback_ onKeyboard:ch withState:kKeyReleased];
  } else {
    [super keyDown:theEvent];
  }
}

#pragma mark -
#pragma mark Accessors

/**
 *  @name addCallbacks
 *  @brief  Add callback for this view
 *  @param[in]  callback  Wrapper for OGLCallbacks interface
 */
-(void) addCallbacks:(OGLCallbacksWrapper*) callback {
  callback_ = callback;
}


@end
