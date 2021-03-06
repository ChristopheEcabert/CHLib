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

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  // Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
  // Insert code here to tear down your application
}

@end
