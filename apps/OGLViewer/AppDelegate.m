//
//  AppDelegate.m
//  OGLViewer
//
//  Created by Christophe Ecabert on 30/07/16.
//  Copyright © 2016 Christophe Ecabert. All rights reserved.
//

#import "AppDelegate.h"
#import "callback_wrapper.h"
#import "ogl_view.h"

@interface AppDelegate () {
  /** Callback */
  OGLCallbacksWrapper* callback_;
}

@property (weak) IBOutlet NSWindow *window;
@property (weak) IBOutlet OGLView* ogl_view;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  // Insert code here to initialize your application
  callback_ = [[OGLCallbacksWrapper alloc] init];
  // Add callback to view
  [_ogl_view addCallbacks:callback_];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
  // Insert code here to tear down your application
}

@end
