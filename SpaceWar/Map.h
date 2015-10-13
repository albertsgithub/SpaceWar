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

typedef enum{
    tag_oneImg,
    tag_twoImg,
    tag_threeImg
}tagMap0;//枚举两张地图背景的交替出现

class Map : public cocos2d::CCLayer
{
public:
    //地图滚动速度
    int speed;
    
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
