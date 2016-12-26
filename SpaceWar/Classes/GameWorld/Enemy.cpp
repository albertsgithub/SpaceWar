//
//  Enemy.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Enemy.h"
#include "Game.h"

Enemy* Enemy::createEnemy(const char* fileName,int _type)
{
    Enemy* enemy = new Enemy();
    if(enemy && enemy->initWithFile(fileName))
    {
        enemy->autorelease();
        enemy->enemyInit(fileName,_type);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}
/**
 * 敌机初始化
 */
void Enemy::enemyInit(const char* fileName,int _type)
{
    //为不同的敌机设置分值以及出现位置
    type=_type;
    if(_type==0)
    {
        scoreValue=200;
        enemyHp=8;
        this->setPosition(ccp(int(CCRANDOM_MINUS1_1()*10)*200+ScreenWidth/2,ScreenHeight+this->getContentSize().height));
    }
    else if(_type==1)
    {
        scoreValue=400;
        enemyHp=10;
        this->setPosition(ccp(ScreenWidth/2,ScreenHeight+this->getContentSize().height));
    }
    else if(_type==2)
    {
        scoreValue=0;
        enemyHp=5;
        this->setPosition(ccp(CCRANDOM_0_1()*ScreenWidth,ScreenHeight+this->getContentSize().height));
    }
    this->scheduleUpdate();
}

/**
 * 三种不同的运动路径
 */
void Enemy::update(float time)
{
    //如果敌机超出屏幕则移除
    if(this->getPositionY() < (-this->getContentSize().height/2))
    {
        Game::sharedWorld()->arrayEnemy->removeObject(this);
        this->removeFromParent();
    }
    
    if (!Game::sharedWorld()->player) return;
    CCMoveTo *action_moveToPlayer = CCMoveTo::create(700, ccp(Game::sharedWorld()->player->getPosition().x,-100));//炸弹移动向主机的动作
    CCEaseExponentialOut *action_speedMoveToPlayer = CCEaseExponentialOut::create(action_moveToPlayer);           //变速动作
    switch (type) {
        case 0:
            this->setPosition(ccpAdd(this->getPosition(), ccp(0.5,-3)));
            break;
        case 1:
            this->runAction(action_moveToPlayer);
            break;
        case 2:
            this->runAction(action_speedMoveToPlayer);
            break;
        default:
            break;
    }
}
