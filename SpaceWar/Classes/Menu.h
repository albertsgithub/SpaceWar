//
//  Menu.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
/****************************
 * 游戏导航菜单
 ****************************/
#ifndef ________Menu__
#define ________Menu__

#include "Prefix.h"

class Menu:public cocos2d::CCLayer
{
public:
    //记录右边飞机的显示隐藏状态
    bool show;
    //创建菜单场景
    static cocos2d::CCScene* scene();
    //初始化菜单
    bool init();
    CREATE_FUNC(Menu);
    //开始游戏
    void playIsPressed();
    //成绩
    void scoreIsPressed();
    //关于
    void aboutIsPressed();
    //设置
    void setIsPressed();
    //关闭开发者介绍灰色框
    void closeUs();
    //打开音乐音效
    void musicOn();
    //关闭音乐音效
    void musicOff();
    //按帧更新
    void update(float time);
};

#endif /* defined(________Menu__) */