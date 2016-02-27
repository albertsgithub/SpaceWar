//
//  Enemy.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Enemy.h"
#include "Game.h"
/**
 * 实例化函数
 */
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
 * 自动创建敌怪对象
 */
void Enemy::autoCreateEnemy()
{
    //一次创建2个敌机
    for (int i =0; i<2; i++)
    {
        Enemy* enemy=NULL;
        int random=CCRANDOM_0_1()*10;
        int randomType;
        
        const char* name;
        if(random>=0 && random<=5)
        {
            name="enemy_red.png";
            randomType=0;
        }
        
        else if(random>=6 && random<=8)
        {
            name="enemy_blue.png";
            randomType=1;
        }
        else if(random>=9 && random<=10)
        {
            name="cohete_on.png";
            //enemy->runAction(Enemy::createAnimate());
            randomType=2;
        }
        enemy=Enemy::createEnemy(name, randomType);
        Game::sharedWorld()->arrayEnemy->addObject(enemy);
        Game::sharedWorld()->addChild(enemy);
    }
}
/**
 * 三种不同的运动路径
 */
void Enemy::update(float time)
{
   // CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo *action_moveToPlayer =CCMoveTo::create(700, ccp(Game::sharedWorld()->playerMajor->getPosition().x,-100));//炸弹移动向主机的动作
    CCEaseExponentialOut *action_speedMoveToPlayer =CCEaseExponentialOut::create(action_moveToPlayer);//变速动作
    
    switch (type)
    {
        case 0:
        {
            this->setPosition(ccpAdd(this->getPosition(), ccp(0.5,-3)));
            break;
        }
        case 1:
        {
            if(Game::sharedWorld()->planeIsExist)
                this->runAction(action_moveToPlayer);
            break;
        }
        case 2:
        {
            if(Game::sharedWorld()->planeIsExist)
                this->runAction(action_speedMoveToPlayer);
        }
        default:
            break;
    }
    //如果敌机超出屏幕则移除
    if(this->getPositionY()< (-this->getContentSize().height/2))
    {
        Game::sharedWorld()->arrayEnemy->removeObject(this);
        this->getParent()->removeChild(this, true);
    }
    
}

/**
 * 制作动画
 */
CCAnimate* Enemy::createAnimate()
{
//    auto animation_enemy = CCAnimation::create();
//    animation_enemy->addSpriteFrameWithFileName("cohete_on.png");
//    animation_enemy->addSpriteFrameWithFileName("cohete_off.png");
//    animation_enemy->setDelayPerUnit(0.1f);
//    animation_enemy->setLoops(-1);
//    animation_enemy->setRestoreOriginalFrame(true);
//    auto animate_boss = CCAnimate::create(animation_enemy);
//    return animate_boss;
}
/**
 * 生命周期结束
 */
void Enemy::onExit()
{
    this->unscheduleUpdate();
    CCSprite::onExit();
}