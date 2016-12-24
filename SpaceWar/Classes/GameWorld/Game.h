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
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBoss.h"
#include "Menu.h"
#include "cocos2d.h"
using namespace cocos2d;

class Game : public CCLayer
{
public:
    /**
     *  游戏数据变量
     */
    int score;
    int killNum;                   // 杀敌数
    int instance;                  // 距离
    int record;                    // 距离存储器
    int diamond_c;                 // 水晶钻石数量
    int diamond_y;                 // 黄钻石数量
    int diamond_r;                 // 红钻石数量
    
    CCLabelTTF* labelScores;       //分数标签
    CCLabelTTF* labelDistance;     //距离标签
    CCLabelTTF* labelKillCount;    //杀敌数标签
    CCLabelTTF* labelDiamond;      //水晶钻石标签
    CCLabelTTF* labelDiamond1;     //黄钻石标签
    CCLabelTTF* labelDiamond2;     //红钻石标签
    
    //飞机
    Plane *playerMajor;
    Plane0 *playerAuxiliary;
    
    //boss
    //EnemyBoss *boss;
    
    // boss是否存在
    bool bossIsExist;
    // 主机是否还存在
    bool planeIsExist;
    // 辅机是否还存在
    bool plane0IsExist;
    // 存放敌怪的数组
    CCArray * arrayEnemy;

public:
    // 创建一个游戏场景
    static CCScene* scene();
    // 获取当前Game的静态实例
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
    
    //游戏失败画面
    void lostGame();
    //隐藏提示
    void showWarn();
    //按帧更新
    void update(float time);
    //显示分数、杀敌数、距离等信息
    void showMessage();
    
    //注册多点触控监听
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
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
