#import "RSSignatureView.h"
#import <React/RCTViewManager.h>
#import <React/RCTEventEmitter.h>

@interface RSSignatureViewManager : RCTViewManager <RCTBridgeModule>
@property (nonatomic, strong) RSSignatureView *signView;
-(void) saveImage:(nonnull NSNumber *)reactTag;
-(void) resetImage:(nonnull NSNumber *)reactTag;
-(void) publishSaveImageEvent:(NSString *) aTempPath withEncoded: (NSString *) aEncoded;
-(void) publishDraggedEvent;
@end
