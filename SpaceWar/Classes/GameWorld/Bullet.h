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
    float speedx;//速度
    //子弹垂直速度
    float speedy;//速度
    
    /**
     * 子弹实例化函数，惨数：贴图资源，x轴水平速度，y轴竖直速度，出现位置
     */
    static Bullet* createBullet(const char* _fileName,float _speedx,float _speedy,CCPoint _position);
    /**
     * 子弹初始化
     */
    void bulletInit(float _speedx,float _speed,CCPoint _position);
    /**
     * 系统安帧更新，改变子弹运动轨迹
     */
    virtual void update(float time);
    /**
     * 生命周期结束
     */
    void onExit();
};
#endif /* defined(________Bullet__) */
