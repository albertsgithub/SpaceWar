//
//  EnemyBullet.h
//  星际联盟
//
//  Created by 919575700@qq.com on 10/30/14.
//
//
#ifndef ________EnemyBullet__
#define ________EnemyBullet__

#include "Prefix.h"
#include "Bullet.h"
#include "Game.h"
#include "Plane.h"
#include "Plane0.h"

class EnemyBullet :public Bullet
{
public:
    //实例化函数
    //static EnemyBullet* createBullet(const char* _fileName,float _speedx,CCPoint _position);
    //void bulletInit(float _speed,CCPoint _position);
    /**
     * 运动方式
     */
    void update(float time);
    //void onExit();
};
#endif