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
#include "cocos2d.h"
using namespace cocos2d;

class Menu:public CCLayer
{
public:
    
    static CCScene* scene();
    bool init();
    virtual void onEnter();
    virtual void update(float time);
    virtual void onExit();
    virtual ~Menu();
    CREATE_FUNC(Menu);
    
    
    // 记录右边飞机的显示隐藏状态
    bool show = true;
    
    void addUI();
    // 开始游戏
    void playIsPressed();
    // 成绩
    void scoreIsPressed();
    // 关于
    void aboutIsPressed();
    // 设置
    void setIsPressed();
    // 关闭开发者介绍灰色框
    void closeUs();
    // 打开音乐音效
    void musicOn();
    // 关闭音乐音效
    void musicOff();
    
};

#endif /* defined(________Menu__) */
