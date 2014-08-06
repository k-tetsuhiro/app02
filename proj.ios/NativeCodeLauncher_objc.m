#import "NativeCodeLauncher_objc.h"

@implementation NativeCodeLauncher

// GameCenterへのログインチェック
+(void)loginGameCenter
{
    //for iOS6+
    if(floor(NSFoundationVersionNumber) >= NSFoundationVersionNumber_iOS_6_0){
        GKLocalPlayer* player = [GKLocalPlayer localPlayer];
        UIViewController* rootController = [UIApplication sharedApplication].keyWindow.rootViewController;
        player.authenticateHandler = ^(UIViewController* ui, NSError* error )
        {
            if( nil != ui )
            {
                NSLog(@"Need to login");
                [rootController presentViewController:ui animated:YES completion:nil];
            }
            else if( player.isAuthenticated )
            {
                NSLog(@"Authenticated");
            }
            else
            {
                NSLog(@"Failed");
            }
        };
    }
    //for iOS6-
    else{
        GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
        
        [localPlayer authenticateWithCompletionHandler:^(NSError *error) {
            if(localPlayer.authenticated){
                NSLog(@"Authenticated");
            }
            else{
                NSLog(@"Not authenticated");
            }
        }];
        
    }
}
// Leaderboardを開く
+(void)openRanking
{
    
    GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
    if(localPlayer.authenticated){
        UIViewController* rootController = [UIApplication sharedApplication].keyWindow.rootViewController;
        
        GKLeaderboardViewController* leaderboardController = [[GKLeaderboardViewController alloc] init];
        leaderboardController.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardController.leaderboardDelegate = (id<GKLeaderboardViewControllerDelegate>)rootController;
        
        [rootController presentModalViewController:leaderboardController animated:YES];
        [leaderboardController release];
    }
    else{
        UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"GameCenterへのログインが必要です。" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
        [alertView show];
        [alertView release];
    }
    
}
// Leaderboardへの得点送信
+(void)postHighScore:(NSNumber *)kind score:(NSNumber *)score;
{
        GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
        if([localPlayer isAuthenticated])
        {
                NSString *idName = @"";
                
                switch ([kind intValue]) {
                        case 1:
                                idName = @"XXX";
                                break;
                        case 2:
                                idName = @"YYY";
                                break;
                        default:
                                break;
                }
                
                GKScore *gkScore = [[GKScore alloc]initWithCategory:idName];
                gkScore.value = [score longLongValue];
                gkScore.context = 1;
                [gkScore reportScoreWithCompletionHandler:^(NSError *error) {
                        if(error)
                        {
                                NSLog(@"Error : %@",error);
                        }
                        else
                        {
                                NSLog(@"Sent highscore.");
                        }
                }];
        }
        else
        {
                NSLog(@"Gamecenter not authenticated.");
        }
}
// Achievementを開く
+(void)openAchievement
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if(localPlayer.authenticated){
        UIViewController* rootController = [UIApplication sharedApplication].keyWindow.rootViewController;
        
        GKAchievementViewController *achievementController = [[GKAchievementViewController alloc]init];
        achievementController.achievementDelegate = (id<GKAchievementViewControllerDelegate>)rootController;
        
        [rootController presentModalViewController:achievementController animated:YES];
        [achievementController release];
    }
    else{
        UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"GameCenterへのログインが必要です。" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
        [alertView show];
        [alertView release];
    }

}
// 達成項目の達成度を送信
+(void)postAchievement:(NSNumber *)kind percent:(NSNumber *)percentComplete
{
        GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
        if([localPlayer isAuthenticated])
        {
                NSString *idName = @"";
                
                switch ([kind intValue]) {
                        case 1:
                                idName = @"XXX";
                                break;
                        case 2:
                                idName = @"YYY";
                                break;
                        default:
                                break;
                }
                
                GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier:idName];
                achievement.percentComplete = [percentComplete doubleValue];
                achievement.showsCompletionBanner = YES;
                [achievement reportAchievementWithCompletionHandler:^(NSError *error) {
                        if(error)
                        {
                                NSLog(@"Error : %@",error);
                        }
                        else
                        {
                                NSLog(@"Sent Achievement.");
                        }
                }];
        }
        else
        {
                NSLog(@"Gamecenter not authenticated.");
        }
}

@end