//
//  Map.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Map.h"
/**
 *  实例化函数
 *
 *  @param fileName 地图的贴图资源
 *  @param speed    地图滚动的速度
 *
 *  @return 返回滚动地图
 */
Map* Map::createMap(const char* fileName,int speed){
    Map* map = new Map();
    if(map && map->create()){
        map->autorelease();
        map->mapInit(fileName);
        map->speed=speed;
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}

/**
 *  地图初始化
 *
 *  @param fileName 地图的贴图资源
 */
void Map::mapInit(const char* fileName)
{
    //第一张地图背景图
    CCSprite * turnImg = CCSprite::create(fileName,CCRectMake(ScreenWidth*0.5, turnImg->getContentSize().height*0.5, ScreenWidth, turnImg->getContentSize().height));
    this->addChild(turnImg,0,tag_oneImg);
    
    //第二张地图背景图
    CCSprite * turnImg2 =CCSprite::create(fileName,CCRectMake(ScreenWidth*0.5, turnImg2->getContentSize().height*1.5, ScreenWidth, turnImg2->getContentSize().height));
    this->addChild(turnImg2,0,tag_twoImg);
    //开启按帧更新
    //this->scheduleUpdate();
}
/**
 *  地图更新
 *
 *  @param time <#time description#>
 */
void Map::update(float time){
    CCSprite* sp1 = (CCSprite*)this->getChildByTag(tag_oneImg);
    CCSprite* sp2 = (CCSprite*)this->getChildByTag(tag_twoImg);
    //当第一张地图超出屏幕外，将其重置坐标,接在最顶的图片上
    if(sp1->getPositionY()<=-sp1->getContentSize().height*0.5)
    {
        sp1->setPosition(ccp(ScreenWidth*0.5,sp1->getContentSize().height*1.5));
    }
    else
    {
        sp1->setPosition(ccpAdd(sp1->getPosition(), ccp(0,speed)));
    }
    //当第二张地图超出屏幕外，将其重置坐标,接在最顶的图片上
    
    if(sp2->getPositionY()<=-sp2->getContentSize().height*0.5)
    {
        sp2->setPosition(ccp(ScreenWidth*0.5,sp2->getContentSize().height*1.5));
    }
    else
    {
        sp2->setPosition(ccpAdd(sp2->getPosition(), ccp(0,speed)));
    }
}
/**
 * 生命周期结束
 */
void Map::onExit(){
    //停止更新
    this->unscheduleUpdate();
    CCLayer::onExit();
}