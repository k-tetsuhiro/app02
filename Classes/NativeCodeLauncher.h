#ifndef _NATIVE_CODE_LAUNCHER_H_
#define _NATIVE_CODE_LAUNCHER_H_

namespace Cocos2dExt {
    class NativeCodeLauncher
    {
    public:
		// GameCenter
        static void loginGameCenter();
        static void openRanking();
        static void postHighScore(int kind,int score);
        static void openAchievement();
        static void postAchievement(int kind,int percentComplete);

    };
}
#endif // _NATIVE_CODE_LAUNCHER_H_