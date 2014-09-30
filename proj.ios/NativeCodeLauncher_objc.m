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
                        //tutorial
                        case 1000:idName = @"com.renerd.app02.clearTutorial";break;
                        
                        //Lv
                        case 1:idName = @"com.renerd.app02.clearLv1";break;
                        case 2:idName = @"com.renerd.app02.clearLv2";break;
                        case 3:idName = @"com.renerd.app02.clearLv3";break;
                        case 4:idName = @"com.renerd.app02.clearLv4";break;
                        case 5:idName = @"com.renerd.app02.clearLv5";break;
                        case 6:idName = @"com.renerd.app02.clearLv6";break;
                        case 7:idName = @"com.renerd.app02.clearLv7";break;
                        case 8:idName = @"com.renerd.app02.clearLv8";break;
                        case 9:idName = @"com.renerd.app02.clearLv9";break;
                        case 10:idName = @"com.renerd.app02.clearLv10";break;
                        case 11:idName = @"com.renerd.app02.clearLv11";break;
                        case 12:idName = @"com.renerd.app02.clearLv12";break;
                        case 13:idName = @"com.renerd.app02.clearLv13";break;
                        case 14:idName = @"com.renerd.app02.clearLv14";break;
                        case 15:idName = @"com.renerd.app02.clearLv15";break;
                        case 16:idName = @"com.renerd.app02.clearLv16";break;
                        case 17:idName = @"com.renerd.app02.clearLv17";break;
                        case 18:idName = @"com.renerd.app02.clearLv18";break;
                        case 19:idName = @"com.renerd.app02.clearLv19";break;
                        case 20:idName = @"com.renerd.app02.clearLv20";break;
                        case 21:idName = @"com.renerd.app02.clearLv21";break;
                        case 22:idName = @"com.renerd.app02.clearLv22";break;
                        case 23:idName = @"com.renerd.app02.clearLv23";break;
                        case 24:idName = @"com.renerd.app02.clearLv24";break;
                        case 25:idName = @"com.renerd.app02.clearLv25";break;
                        case 26:idName = @"com.renerd.app02.clearLv26";break;
                        case 27:idName = @"com.renerd.app02.clearLv27";break;
                        case 28:idName = @"com.renerd.app02.clearLv28";break;
                        case 29:idName = @"com.renerd.app02.clearLv29";break;
                        case 30:idName = @"com.renerd.app02.clearLv30";break;
                        default:break;
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