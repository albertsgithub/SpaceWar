//
//  SpaceWarAppDelegate.cpp
//  SpaceWar
//
//  Created by 919575700@qq.com on 10/12/15.
//  Copyright __MyCompanyName__ 2015. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Menu.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

/**
 * 自定义生命周期日志类
 */
class LifeCircleLogger
{
    string m_msg;
public:
    LifeCircleLogger();
    LifeCircleLogger(const string& msg):m_msg(msg)
    {
        CCLog("%s BENGINS!",m_msg.c_str());
    }
    ~LifeCircleLogger(){CCLog("%s ENDS!",m_msg.c_str());}
};

#define LOG_FUNCTION_LIFE LifeCircleLogger(__FUNCTION__);
AppDelegate::AppDelegate()
{
    LOG_FUNCTION_LIFE
}

AppDelegate::~AppDelegate()
{
}

/**
 * 程序启动入口
 */
bool AppDelegate::applicationDidFinishLaunching()
{
    // 0.初始化director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // 1.调试选项：在屏幕左下角实时显示对象数目、帧率等信息
    pDirector->setDisplayStats(true);
    
    // 2.设置游戏动画FPS帧率
    pDirector->setAnimationInterval(1.0 / 60);
    
    // 3.改变游戏速率
    //pDirector->getScheduler()->setTimeScale(2);
    
    // 4.创建一个入口场景，此场景可以自动释放
    CCScene *pScene =Menu::scene();
    pDirector->runWithScene(pScene);
    
    return true;
}
#pragma mark -应用程序生命周期代理
/**
 * 进入后台
 * This function will be called when the app is inactive. When comes a phone call,it's be invoked too
 */
void AppDelegate::applicationDidEnterBackground()
{
    LOG_FUNCTION_LIFE
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

/**
 * 回到前台
 * this function will be called when the app is active again
 */
void AppDelegate::applicationWillEnterForeground()
{
    LOG_FUNCTION_LIFE
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}