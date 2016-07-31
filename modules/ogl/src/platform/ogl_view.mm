/**
 *  @file   ogl_view.mm
 *  @brief  Custom Cocoa OpenGL view
 *
 *  @author Christophe Ecabert
 *  @date   31/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#import <OpenGL/gl3.h>

#import "chlib/ogl/platform/ogl_view.h"

@implementation OGLView

/**
 *  @name awakeFromNib
 *  @fn -(void) awakeFromNib
 *  @brief  Mehtod invoked when Nib file is loaded
 */
-(void) awakeFromNib {
  NSLog(@"Awake from nib ...");
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
  NSOpenGLPixelFormat* frmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
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

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  [[self openGLContext] flushBuffer];
}

@end
