/**
 *  @file   ogl_view.mm
 *  @brief  Custom Cocoa OpenGL view
 *  @see    https://developer.apple.com/library/mac/qa/qa1385/_index.html
 *
 *  @author Christophe Ecabert
 *  @date   31/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <OpenGL/gl3.h>

#import "ogl_view.h"
#import "callback_wrapper.h"

@interface OGLView() {
  /** Display link for managing rendering thread */
  CVDisplayLinkRef display_link_;
  /** OGL Callback wrapper */
  OGLCallbacksWrapper* callback_;
}
@end

@implementation OGLView

#pragma mark -
#pragma mark OpenGL Event

/**
 *  @name prepareOpenGL
 *  @brief  Create OpenGL context and CVDisplayLink
 */
-(void) prepareOpenGL {
  // The reshape function may have changed the thread to which our OpenGL
  // context is attached before prepareOpenGL and initGL are called.  So call
  // makeCurrentContext to ensure that our OpenGL context current to this
  // thread (i.e. makeCurrentContext directs all OpenGL calls on this thread
  // to [self openGLContext])
  [[self openGLContext] makeCurrentContext];
  // Synchronize buffer swaps with vertical refresh rate
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
  // Create a display link capable of being used with all active displays
  CVDisplayLinkCreateWithActiveCGDisplays(&display_link_);
  // Set the renderer output callback function
  CVDisplayLinkSetOutputCallback(display_link_,
                                 &renderCallback,
                                 (__bridge void * )self);
  // Set the display link for the current renderer
  CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
  CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
  CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(display_link_,
                                                    cglContext,
                                                    cglPixelFormat);
  
  // Activate the display link
  CVDisplayLinkStart(display_link_);
}

/**
 *  @name   getFrameForTime
 *  @brief  Invoked when rendering is needed
 */

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime {
  // There is no autorelease pool when this method is called
  // because it will be called from a background thread.
  // It's important to create one or app can leak objects.
  @autoreleasepool {
    [self drawView];
  }
  return kCVReturnSuccess;
}

/**
 *  @name   renderCallback
 *  @brief  This is the renderer output callback function
 */
static CVReturn renderCallback(CVDisplayLinkRef displayLink,
                               const CVTimeStamp* now,
                               const CVTimeStamp* outputTime,
                               CVOptionFlags flagsIn,
                               CVOptionFlags* flagsOut,
                               void* displayLinkContext) {
  CVReturn res = [(__bridge OGLView*) displayLinkContext getFrameForTime:outputTime];
  return res;
}

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
    NSOpenGLPFADepthSize, 32,
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
    // Set bounds
    NSRect b = [self bounds];
    glViewport(0, 0, b.size.width, b.size.height);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
  }
}

-(void) drawRect:(NSRect)dirtyRect {
  // Called during resize operations
  // Avoid flickering during resize by drawiing
  [self drawView];
}

-(void) drawView {
  [[self openGLContext] makeCurrentContext];
  // We draw on a secondary thread through the display link
  // When resizing the view, -reshape is called automatically on the main
  // thread. Add a mutex around to avoid the threads accessing the context
  // simultaneously when resizing
  CGLLockContext([[self openGLContext] CGLContextObj]);
  if (callback_) {
    [callback_ onRender];
  } else {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
  }
  // Swap buffer
  CGLFlushDrawable([[self openGLContext] CGLContextObj]);
  CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

- (void) windowWillClose:(NSNotification*)notification {
  // Stop the display link when the window is closing because default
  // OpenGL render buffers will be destroyed.  If display link continues to
  // fire without renderbuffers, OpenGL draw calls will set errors.
  CVDisplayLinkStop(display_link_);
}

- (void)reshape {
  [super reshape];
  
  // We draw on a secondary thread through the display link. However, when
  // resizing the view, -drawRect is called on the main thread.
  // Add a mutex around to avoid the threads accessing the context
  // simultaneously when resizing.
  CGLLockContext([[self openGLContext] CGLContextObj]);
  
  // Get the view size in Points
  NSRect viewRectPoints = [self bounds];
  // Set the new dimensions in our renderer
  glViewport(0, 0, viewRectPoints.size.width, viewRectPoints.size.height);
  
  //TODO Camera aspect ratio should be updated
  if (callback_) {
    [callback_ onResizeWidth:viewRectPoints.size.width
                   andHeight:viewRectPoints.size.height];
  }
  
  // Unlock context
  CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

/** 
 *  @name   dealloc
 *  @brief  destructor, do not need to call [super dealloc]
 *  @see  http://stackoverflow.com/questions/7292119/custom-dealloc-and-arc-objective-c
 */
-(void) dealloc {
  // Stop the display link BEFORE releasing anything in the view
  // otherwise the display link thread may call into the view and crash
  // when it encounters something that has been release
  CVDisplayLinkStop(display_link_);
  CVDisplayLinkRelease(display_link_);
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
    //[callback_ onMouseClick: kMouseLeftButton withState:kKeyPressed at:&pos];
    [callback_ onMouseMove:&pos];
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
