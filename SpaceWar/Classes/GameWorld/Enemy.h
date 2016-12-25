//
//  Enemy.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#ifndef ________Enemy__
#define ________Enemy__
#include "cocos2d.h"
using namespace cocos2d;

class Enemy : public CCSprite
{
public:
    //敌机的价值
    int scoreValue;
    //敌机类型
    int type;
    //敌机生命值
    int enemyHp;
    
    static Enemy* createEnemy(const char* fileName,int _type);

    void enemyInit(const char* fileName,int _type);
    
    void autoCreateEnemy();

    CCAnimate* createAnimate();

    virtual void update(float time);
};

#endif /* defined(________Enemy__) */
