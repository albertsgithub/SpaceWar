//
//  Founction.h
//  星际联盟
//
//  Created by 919575700@qq.com on 4/7/14.
//
//
#ifndef ________Prefix__
#define ________Prefix__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace std;
using namespace cocos2d;
/**
 * 屏幕尺寸
 */
#define ScreenSize CCDirector::sharedDirector()->getWinSize()
#define ScreenHeight CCDirector::sharedDirector()->getWinSize().height
#define ScreenWidth CCDirector::sharedDirector()->getWinSize().width

//字体宏
#define font1 "迷你简萝卜.ttf"
#define font2 "PAGANINI.TTF"
//转场时间
#define turnTime 0.2
//转场类型
#define transition CCTransitionCrossFade
//点击音效
#define clickEffect "clickEffect.mp3"

//转换成string类型
template<typename T>
string Convert2String(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

#endif /* defined(________Prefix__) */