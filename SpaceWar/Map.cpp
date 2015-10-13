//
//  Map.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Map.h"
/**
 * 实例化函数
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
 * 地图初始化
 */
void Map::mapInit(const char* fileName)
{
    //第一张地图背景图
    CCSprite * turnImg = CCSprite::create(fileName);
    turnImg->setPosition(ccp(turnImg->getContentSize().width*0.5,turnImg->getContentSize().height*0.5));
    this->addChild(turnImg,0,tag_oneImg);
    
    //第二张地图背景图
    CCSprite * turnImg2 =CCSprite::create(fileName);
    turnImg2->setPosition(ccp(turnImg2->getContentSize().width*0.5,turnImg2->getContentSize().height*1.5));
    this->addChild(turnImg2,0,tag_twoImg);
    //第三张地图背景图
    CCSprite * turnImg3 =CCSprite::create(fileName);
    turnImg3->setPosition(ccp(turnImg3->getContentSize().width*0.5,turnImg3->getContentSize().height*2.5));
    this->addChild(turnImg3,0,tag_threeImg);
    
    this->scheduleUpdate();
}
/**
 * 地图更新
 */
void Map::update(float time){
    CCSprite* sp1 = (CCSprite*)this->getChildByTag(tag_oneImg);
    CCSprite* sp2 = (CCSprite*)this->getChildByTag(tag_twoImg);
    CCSprite* sp3 = (CCSprite*)this->getChildByTag(tag_threeImg);
    //当第一张地图超出屏幕外，将其重置坐标,接在最顶的图片上
    if(sp1->getPositionY()<=-sp1->getContentSize().height*0.5){
        sp1->setPosition(ccp(sp1->getContentSize().width*0.5,sp1->getContentSize().height*2.5));
    }else{
        sp1->setPosition(ccpAdd(sp1->getPosition(), ccp(0,speed)));
    }
    //当第二张地图超出屏幕外，将其重置坐标,接在最顶的图片上
    
    if(sp2->getPositionY()<=-sp2->getContentSize().height*0.5){
        sp2->setPosition(ccp(sp2->getContentSize().width*0.5,sp2->getContentSize().height*2.5));
    }else{
        sp2->setPosition(ccpAdd(sp2->getPosition(), ccp(0,speed)));
    }
    //当第三张地图超出屏幕外，将其重置坐标,接在最顶的图片上
    
    if(sp3->getPositionY()<=-sp3->getContentSize().height*0.5){
        sp3->setPosition(ccp(sp3->getContentSize().width*0.5,sp3->getContentSize().height*2.5));
    }else{
        sp3->setPosition(ccpAdd(sp3->getPosition(), ccp(0,speed)));
    }
}
/**
 * 生命周期结束
 */
void Map::onExit(){
    this->unscheduleUpdate();
    CCLayer::onExit();
}
