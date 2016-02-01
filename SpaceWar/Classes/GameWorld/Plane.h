//
//  Plane.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#ifndef ________Plane__
#define ________Plane__

#include "Prefix.h"
/**
 * 主机精灵类
 */
class Plane : public cocos2d::CCSprite
{
public:
    //血量
    int hp;
    //血量最大值
    int hpMax;
    //是否处于无敌时间
    bool isStrong;
    //闪烁变量
    bool show;
    
    //主机静态单例
    static Plane* createPlayer(const char* fileName,int _hpMax,int _hp,float x,float y);
    //初始化主机，参数为：贴图资源名，最大血量，血量，起始坐标
    void playerInit(const char* fileName,int _hpMax,int _hp,float x,float y);
    //处理无敌
    void startStrong(float strongTime);
    //无敌时的闪烁
    void shine();
    //结束无敌
    void endStrong();
    //主角吃到道具
    void eatTool();
    //系统帧更新，检测与敌机碰撞
    void update(float time);
    //制作主机动画
    virtual CCAnimate* createAnimate(const char* fileName);
    //与敌人碰撞处理
    virtual void collideWithEnemy();
};

#endif /* defined(________Plane__) */
