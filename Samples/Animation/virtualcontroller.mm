#import "virtualcontroller.hpp"
#if __APPLE__

#import <Foundation/Foundation.h>

#if TARGET_OS_IOS
#import <GameController/GameController.h>
#import <GameController/GCVirtualController.h>
#endif

#endif

GCVirtualController *_virtualController;

void InitVirtualController() {
#if TARGET_OS_IOS
    GCVirtualControllerConfiguration *config = [[GCVirtualControllerConfiguration alloc] init];
   // Add elements that your controller-handling code currently supports.
   config.elements = [NSSet setWithArray:@[
       GCInputButtonA,
       GCInputButtonB,
       GCInputButtonX,
       GCInputButtonY,
       GCInputLeftThumbstick,
       GCInputRightThumbstick]];
    config.hidden = NO;
    _virtualController = [[GCVirtualController alloc] initWithConfiguration:config];
    
    [_virtualController connectWithReplyHandler:nil];
#endif
}
