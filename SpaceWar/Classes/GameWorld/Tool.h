//
//  Tool.h
//  PlaneDemo
//
//  Created by mac on 14-3-31.
//
/******************************
 * 游戏中的道具类
 ******************************/
#ifndef __PlaneDemo__Prop__
#define __PlaneDemo__Prop__
#include "cocos2d.h"
using namespace cocos2d;

class Tool:public CCSprite
{
public:
    //道具类型:钻石、补血、无敌武器
    int type;
    
    static Tool* createTool(const char* fileName,int _type,CCPoint _position);
    void autoCreateTool(CCPoint _enenmyPosition);
    void toolInit(int _type,CCPoint _position);
    virtual void update(float time);
    void beGeted();
};
#endif /* defined(__PlaneDemo__Prop__) */
