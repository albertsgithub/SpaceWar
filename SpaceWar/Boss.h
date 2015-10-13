#ifndef ________Boss__
#define ________Boss__

#include "Prefix.h"
#include "Game.h"
#include "EnemyBullet.h"

class Boss :public cocos2d::CCSprite
{
public:
    //boss类型
    int type;
    //boss生命值
    int bossHp;
    
    /**
     * 实例化函数
     */
    static Boss* createBoss(const char* fileName,int _type);
    /**
     * boss初始化
     */
    void bossInit(const char* fileName,int _type);
    /**
     * 创建boss动画
     */
    CCAnimate *createAnimate2(const char* fileName);
    CCAnimate *createAnimate3(const char* fileName);
    /**
     * 产生子弹
     */
    void createBullet();
    /**
     * 退出生命周期
     */
    void onExit();
};
#endif