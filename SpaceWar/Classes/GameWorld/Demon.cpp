//
//  Demon.cpp
//  SpaceWar
//
//  Created by Xinhou Jiang on 23/12/16.
//
//

#include "Demon.h"
#include "Game.h"
#include "EnemyBullet.h"

Demon* Demon::createDemon(const char *fileName, int _type)
{
    Demon* boss = new Demon();
    if(boss && boss->initWithFile(fileName))
    {
        boss->autorelease();
        boss->bossInit(fileName,_type);
        return boss;
    }
    CC_SAFE_DELETE(boss);
    return NULL;
}

void Demon::bossInit(const char* fileName,int type)
{
    //确定boss类型
    this->type = type;
    if(this->type == 0)
    {
        bossHp = 500;
    }
    else if(this->type == 1)
    {
        bossHp = 600;
    }
    else if(this->type == 2)
    {
        bossHp = 800;
    }
    
    this->setScale(1.5);//缩放
    this->setPosition(ccp(ScreenWidth/2,ScreenHeight+this->getContentSize().height));
    
    // 帧动画
    this->runAction(createAnimate(this->type));
    // 运动动画
    this->runAction(CCMoveTo::create(2, ccp(ScreenWidth/2,ScreenHeight/1.5)));
    // 摆动动画
    CCMoveTo *right=CCMoveTo::create(3, ccp(ScreenWidth-this->getContentSize().width/2,ScreenHeight/1.5));
    CCMoveTo *left=CCMoveTo::create(3, ccp(this->getContentSize().width/2,ScreenHeight/1.5));
    CCSequence *sequence=CCSequence::create(right,left,NULL);
    this->runAction(CCRepeatForever::create(sequence));
    this->scheduleUpdate();
}

/**
 * 制作boss动画
 */
CCAnimate* Demon::createAnimate(int type) {
    auto animation_boss = CCAnimation::create();
    // 添加帧
    if (type == 0) {
        
    }else if (type == 1) {
        for (int i = 1; i <= 8; i++) {
            CCString *filename = CCString::create("");
            filename->initWithFormat("%d.png", i);
            animation_boss->addSpriteFrameWithFileName(filename->getCString());
        }
    }else if(type == 2) {
        for (int i = 1; i <= 11; i++) {
            CCString *filename = CCString::create("");
            filename->initWithFormat("purple%d.png", i);
            animation_boss->addSpriteFrameWithFileName(filename->getCString());
        }
    }else {
        return NULL;
    }
    animation_boss->setDelayPerUnit(0.2f);
    animation_boss->setLoops(-1);
    animation_boss->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_boss);
    return animate_wellcome;
}
