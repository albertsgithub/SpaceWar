//
//  Boss.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 4/7/14.
//
//
#include "EnemyBoss.h"

/**
 * boss静态单例
 */
 EnemyBoss* EnemyBoss::createBoss(const char *fileName, int _type)
{
    EnemyBoss* boss = new EnemyBoss();
    if(boss && boss->initWithFile(fileName))
    {
        boss->autorelease();
        boss->bossInit(fileName,_type);
        return boss;
    }
    CC_SAFE_DELETE(boss);
    return NULL;
}

/**
 * boss初始化
 */
void EnemyBoss::bossInit(const char* fileName,int _type)
{
    //确定boss类型
    type=_type;
    if(_type==0)
    {
        bossHp=500;
    }
    else if(_type==1)
    {
        bossHp=600;
    }
    else if(_type==2)
    {
        bossHp=800;
    }
    //播放动画
    if (type==1)
        this->runAction(EnemyBoss::createAnimate2(fileName));
    if (type==2)
        this->runAction(EnemyBoss::createAnimate3(fileName));
    this->setScale(1.5);//缩放
    this->setPosition(ccp(ScreenWidth/2,ScreenHeight+this->getContentSize().height));
    //动画序列
    this->runAction(CCMoveTo::create(2, ccp(ScreenWidth/2,ScreenHeight/1.5)));
    //摆动动画
    CCMoveTo *right=CCMoveTo::create(3, ccp(ScreenWidth-this->getContentSize().width/2,ScreenHeight/1.5));
    CCMoveTo *left=CCMoveTo::create(3, ccp(this->getContentSize().width/2,ScreenHeight/1.5));
    CCSequence *sequence=CCSequence::create(right,left,NULL);
    this->runAction(CCRepeatForever::create(sequence));
    this->scheduleUpdate();
    //boss子弹
    this->schedule(schedule_selector(EnemyBoss::createBullet), 1.5, -1, 3);//每1.5产生一次，无限循环，延时3s
}

/**
 * 产生boss子弹
 */
void EnemyBoss::createBullet()
{
    if(type==1)
    Game::sharedWorld()->addChild(EnemyBullet::createBullet("bossBullet1.png",0,-6,ccp(this->getPosition().x,this->getPosition().y)));
    if(type==2)
    Game::sharedWorld()->addChild(EnemyBullet::createBullet("bossBullet1.png",0,-6,ccp(this->getPosition().x,this->getPosition().y)));
}

/**
 * 制作boss动画
 */
CCAnimate* EnemyBoss::createAnimate2(const char* fileName)
{
    auto animation_boss = CCAnimation::create();
    // 添加帧
    for (int i = 1; i <= 8; i++) {
        CCString *filename = CCString::create("");
        filename->initWithFormat("%d.png", i);
        animation_boss->addSpriteFrameWithFileName(filename->getCString());
    }
    animation_boss->setDelayPerUnit(0.2f);
    animation_boss->setLoops(-1);
    animation_boss->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_boss);
    return animate_wellcome;
}

CCAnimate* EnemyBoss::createAnimate3(const char* fileName)
{
    auto animation_boss = CCAnimation::create();
    // 添加帧
    for (int i = 1; i <= 11; i++) {
        CCString *filename = CCString::create("");
        filename->initWithFormat("purple%d.png", i);
        animation_boss->addSpriteFrameWithFileName(filename->getCString());
    }
    animation_boss->setDelayPerUnit(0.2f);
    animation_boss->setLoops(-1);
    animation_boss->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_boss);
    return animate_wellcome;
}

/**
 * 退出生命周期
 */
void EnemyBoss::onExit()
{
    CCSprite::onExit();
    this->unscheduleUpdate();
    this->unscheduleAllSelectors();
}
