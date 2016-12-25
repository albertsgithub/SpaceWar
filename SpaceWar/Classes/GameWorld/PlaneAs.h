//
//  Plane0.h
//  星际联盟
//
//  Created by 919575700@qq.com on 4/2/14.
//
//
#ifndef ________Plane0__
#define ________Plane0__
#include "cocos2d.h"
using namespace cocos2d;

#include "Plane.h"

class PlaneAs : public Plane
{
public:
    static PlaneAs* createPlayer(const char* fileName,int _hpMax,int _hp,float x,float y);
    void collideWithEnemy();
    CCAnimate* createAnimate(const char *fileName);
};
#endif /* defined(________Plane0__) */
