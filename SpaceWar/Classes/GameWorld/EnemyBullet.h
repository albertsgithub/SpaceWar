//
//  EnemyBullet.h
//  星际联盟
//
//  Created by 919575700@qq.com on 10/30/14.
//
//
#ifndef ________EnemyBullet__
#define ________EnemyBullet__

#include "Bullet.h"
#include "Game.h"
#include "Plane.h"
#include "PlaneAs.h"
#include "cocos2d.h"
using namespace cocos2d;

class EnemyBullet :public Bullet
{
public:

    static EnemyBullet* createBullet(const char* _fileName,float _speedx,CCPoint _position);
    void bulletInit(float _speed,CCPoint _position);
    void update(float time);
};
#endif
