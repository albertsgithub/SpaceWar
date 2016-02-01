//
//  Enemy.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#ifndef ________Enemy__
#define ________Enemy__

#include "Prefix.h"

class Enemy : public cocos2d::CCSprite
{
public:
    //敌机的价值
    int scoreValue;
    //敌机类型
    int type;
    //敌机生命值
    int enemyHp;
    
    /**
     * 实例化函数
     */
    static Enemy* createEnemy(const char* fileName,int _type);
    /**
     * 敌机初始化
     */
    void enemyInit(const char* fileName,int _type);
    /**
     * 自动创建敌机
     */
    void autoCreateEnemy();
    /**
     * 创建敌机动画
     */
    CCAnimate* createAnimate();
    /**
     * 敌人运动方式
     */
    void update(float time);
    /**
     * 生命周期结束
     */
    void onExit();
};

#endif /* defined(________Enemy__) */
