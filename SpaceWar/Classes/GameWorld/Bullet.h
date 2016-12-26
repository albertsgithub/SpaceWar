//
//  Bullet.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#ifndef ________Bullet__
#define ________Bullet__
#include "cocos2d.h"
using namespace cocos2d;

class Bullet :public CCSprite
{
public:
    //子弹水平速度
    float speedx;
    //子弹垂直速度
    float speedy;
    
    /*子弹实例化函数，惨数：贴图资源，x轴水平速度，y轴竖直速度，出现位置*/
    static Bullet* createBullet(const char* _fileName,float _speedx,float _speedy,CCPoint _position);
    void bulletInit(float _speedx,float _speed,CCPoint _position);
    virtual void update(float time);
    void move();
};
#endif /* defined(________Bullet__) */
