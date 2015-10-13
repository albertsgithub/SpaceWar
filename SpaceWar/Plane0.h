//
//  Plane0.h
//  星际联盟
//
//  Created by 919575700@qq.com on 4/2/14.
//
//
#ifndef ________Plane0__
#define ________Plane0__

#include "Prefix.h"
#include "Plane.h"

class Plane0 : public Plane
{
public:
    /**
     * 辅机静态单例
     */
    static Plane0* createPlayer(const char* fileName,int _hpMax,int _hp,float x,float y);
    /**
     * 重载主机碰撞检测函数
     */
    void collideWithEnemy();
    /**
     * 主机已经死亡
     */
    void playerWasDead();
    /**
     * 重载制作动画函数
     */
    CCAnimate* createAnimate(const char *fileName);
};
#endif /* defined(________Plane0__) */
