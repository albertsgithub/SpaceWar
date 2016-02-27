//
//  Map.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//

#ifndef ________Map__
#define ________Map__

#include "Prefix.h"

class Map : public cocos2d::CCLayer
{
public:
    //地图滚动速度
    int speed;
    
    //两张地图
    CCSprite * turnImg;
    CCSprite * turnImg2;
    
    //实例化函数
    static Map* createMap(const char* fileName,int speed);
    //地图初始化
    void mapInit(const char* fileName);
    //地图更新
    void update(float time);
    //生命周期函数的退出
    virtual void onExit();
};

#endif /* defined(________Map__) */