//
//  Game.h
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#ifndef ________Game__
#define ________Game__

#include "Tool.h"
#include "Plane.h"
#include "Plane0.h"
#include "HMap.h"
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"
#include "Menu.h"
#include "Prefix.h"

class Game : public cocos2d::CCLayer
{
public:
    //分数
    int score;
    //杀敌数
    int killNum;
    //距离
    int instance;
    //距离存储器
    int record;
    //黄钻石
    int diamond_y;
    //紫钻石
    int diamond_c;
    //红钻石
    int diamond_r;
    //boss是否存在
    bool bossIsExist;
    //主机是否还存在
    bool planeIsExist;
    //辅机是否还存在
    bool plane0IsExist;
    //存放敌怪的数组
    CCArray * arrayEnemy;

public:
    //创建一个游戏场景
    static cocos2d::CCScene* scene();
    //获取当前Game的静态实例
    static Game * sharedWorld();
    CREATE_FUNC(Game);
    //游戏画面初始化
    virtual bool init();
    //刷新飞行距离
    void setDistance();
    //加分
    void addScore(float _value);
    //加杀敌数
    void addKillCount(float _value);
    //计算两点之间距离
    float Distance(CCPoint point1,CCPoint point2);
    //产生子弹、敌机
    void createBullet();
    void createBullet0();
    void createEnemy();
    //返回主机对象实例
    Plane* getPlayer();
    Plane* getPlayer0();
    //游戏失败画面
    void lostGame();
    //隐藏提示
    void showWarn();
    //按帧更新
    void update(float time);
    //注册多点触控监听
    void registerWithTouchDispatcher(void);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    //血量显示
    void showHp();
    //显示分数、杀敌数、距离等信息
    void showMessage();
    //游戏中的操作
    void gameOperation();
    //暂停游戏
    void pauseGame();
    //继续游戏
    void resumeGame();
    //返回主菜单
    void goHome();
    //退出处理
    void onExit();
    //析构函数
    virtual ~Game();
};
#endif /* defined(________Game__) */
