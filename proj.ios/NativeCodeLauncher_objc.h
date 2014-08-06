#import <GameKit/GameKit.h>
@interface NativeCodeLauncher : NSObject

// GameCenter
+(void)loginGameCenter;
+(void)openRanking;
+(void)postHighScore:(NSNumber *)kind score:(NSNumber *)score;
+(void)openAchievement;
+(void)postAchievement:(NSNumber *)kind percent:(NSNumber *)percentComplete;

@end