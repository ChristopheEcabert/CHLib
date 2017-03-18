//
//  OGLRootViewController.m
//  Apps
//
//  Created by Christophe Ecabert on 23/08/16.
//  Copyright © 2016 Christophe Ecabert. All rights reserved.
//

#import "OGLRootViewController.h"
#import "apps_wrapper.h"
#import "callback_wrapper.h"
#import "ogl_view.h"


@interface OGLRootViewController () {
  /** Apps */
  AppsWrapper* app_;
  /** Callback */
  OGLCallbacksWrapper* callback_;
  /** Apps config files */
  NSMutableArray* app_configs_;
}
/** OpenGL View */
@property (weak) IBOutlet OGLView* ogl_view;
/** Application selector */
@property (weak) IBOutlet NSPopUpButton* app_selector;

/**
 *  @name   initAppSelector
 *  @brief  Initialize selector with content of file : app_info.plist
 */
-(void) initAppSelector;

@end

@implementation OGLRootViewController

- (void)viewDidLoad {
  [super viewDidLoad];
}

-(void) viewDidAppear {
  [super viewDidAppear];
  // Populate app selector + Init apps
  [self initAppSelector];
}

#pragma mark -
#pragma mark App Selector

-(void) initAppSelector {
  // Populate selector
  // Get path
  NSString* app_config = [[NSBundle mainBundle] pathForResource:@"app_info"
                                                         ofType:@"plist"];
  if (app_config) {
    // Get all apps
    NSArray* apps = [NSArray arrayWithContentsOfFile:app_config];
    // Loop
    if (!app_configs_) {
      app_configs_ = [[NSMutableArray alloc] initWithCapacity: [apps count]];
    }
    NSUInteger idx = 0;
    NSString* default_name;
    NSString* default_path;
    for (NSDictionary* app in apps) {
      NSString* app_name = [app objectForKey:@"Name"];
      NSString* app_path = [[NSBundle mainBundle] pathForResource:[app objectForKey:@"Path"]
                                                           ofType:@"xml"] ;
      [app_configs_ insertObject:app_path atIndex:idx];
      [self.app_selector insertItemWithTitle:app_name atIndex:idx];
      if (!idx) {
        default_name = app_name;
        default_path = app_path;
      }
      idx++;
    }
    // Init default apps, first one in the list -> apps[0]
    if (!app_) {
      app_ = [[AppsWrapper alloc] initApp: default_name
                               withConfig:default_path
                                 withSize:[self.ogl_view bounds].size];
      callback_ = [[OGLCallbacksWrapper alloc]
                   initWithPointer:[app_ callbacks]];
      
    } else {
      [app_ loadApp:default_name withConfig:default_path];
      [callback_ setPointer: [app_ callbacks]];
    }
    // Set callback
    [self.ogl_view addCallbacks:callback_];
  }
}

- (IBAction)appSelectorClicked:(id)sender {  
  NSMenuItem* item = [self.app_selector selectedItem];
  NSString* item_name = [item title];
  NSInteger item_idx = [self.app_selector indexOfItemWithTitle: item_name];
  // Disable rendering
  [self.ogl_view addCallbacks:nil];
  // Load app
  [app_ loadApp: item_name
     withConfig: [app_configs_ objectAtIndex: item_idx]];
  // Update callback
  if (!callback_) {
    callback_ = [[OGLCallbacksWrapper alloc] initWithPointer:[app_ callbacks]];
  } else {
    [callback_ setPointer:[app_ callbacks]];
  }
  // Set callback to OGLView
  [self.ogl_view addCallbacks:callback_];
}

@end
