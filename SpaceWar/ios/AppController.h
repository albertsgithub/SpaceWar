//
//  SpaceWarAppController.h
//  SpaceWar
//
//  Created by 919575700@qq.com on 10/12/15.
//  Copyright __MyCompanyName__ 2015. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

