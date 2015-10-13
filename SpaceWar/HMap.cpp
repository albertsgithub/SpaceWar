//
//  Plane0.h
//  星际联盟
//
//  Created by 919575700@qq.com on 4/2/14.
//
#include "HMap.h"
/**
 * 创建地图单例
 */
HMap* HMap::createMap(const char* fileName){
    HMap* map = new HMap();
    if(map && map->create()){
        map->autorelease();
        map->mapInit(fileName);
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}
/**
 * 初始化地图
 */
void HMap::mapInit(const char* fileName){
    //创建第一张地图背景图
    CCSprite * turnImg =CCSprite::create(fileName);
    turnImg->setPosition(ccp(turnImg->getContentSize().width*0.5,turnImg->getContentSize().height*0.5));
    this->addChild(turnImg,0,tag_oneImg0);
    //创建第二张地图背景图，用于交替循环
    CCSprite * turnImg2 =CCSprite::create(fileName);
    turnImg2->setPosition(ccp(turnImg2->getContentSize().width*0.5,turnImg2->getContentSize().height*1.5));
    this->addChild(turnImg2,0,tag_twoImg0);
    //开启刷新
    this->scheduleUpdate();
}
/**
 * 系统按帧更新检测
 */
void HMap::update(float time){
    CCSprite* sp1 = (CCSprite*)this->getChildByTag(tag_oneImg0);
    //当第一张地图超出屏幕外，将其重置坐标,接在当前显示的图片下
    if(sp1->getPositionY()<=-sp1->getContentSize().height*0.5){
        sp1->setPosition(ccp(sp1->getContentSize().width*0.5,sp1->getContentSize().height*1.5f-1));
    }else{
        sp1->setPosition(ccpAdd(sp1->getPosition(), ccp(0,-1)));
    }
    //当第二张地图超出屏幕外，将其重置坐标,接在当前显示的图片下
    CCSprite* sp2 = (CCSprite*)this->getChildByTag(tag_twoImg0);
    if(sp2->getPositionY()<=-sp2->getContentSize().height*0.5){
        sp2->setPosition(ccp(sp2->getContentSize().width*0.5,sp2->getContentSize().height*1.5f-1));
    }else{
        sp2->setPosition(ccpAdd(sp2->getPosition(), ccp(0,-1)));
    }
}
/**
 * 退出生命周期
 */
void HMap::onExit(){
    CCLayer::onExit();
    //解除更新函数
    this->unscheduleUpdate();
}
