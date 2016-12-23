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
    
    /**
     * 道具静态单例
     */
    static Tool* createTool(const char* fileName,int _type,CCPoint _position);
    /**
     * 自动产生道具
     */
    void autoCreateTool(CCPoint _enenmyPosition);
    /**
     * 道具初始化
     */
    void toolInit(int _type,CCPoint _position);
    /**
     * 系统安帧更新
     */
    void update(float time);
    /**
     * 检测是否被主角得到
     */
    void beGeted();
    /**
     * 退出生命周期
     */
    virtual void onExit();
};
#endif /* defined(__PlaneDemo__Prop__) */
