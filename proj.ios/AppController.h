#import <UIKit/UIKit.h>

@class RootViewController;

extern "C"{
#import "GADBannerView.h"
};

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate, UIApplicationDelegate>{
    UIWindow *window;
    RootViewController *viewController;
    
    GADBannerView *bannerView_;
}

@end