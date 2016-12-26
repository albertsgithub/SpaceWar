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
#include "PlaneAs.h"
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Demon.h"
#include "Menu.h"
#include "cocos2d.h"
using namespace cocos2d;

typedef enum {
    GAME_SINGLE,
    GAME_DOUBLE
}GAME_TYPE;

class Game : public CCLayer
{
    
    CREATE_FUNC(Game);
    virtual bool init();
    virtual void update(float time);

public:
    static CCScene* scene();
    static Game * sharedWorld();
    /** 游戏数据变量 **/
    int level = 1;           // boss等级
    int score = 0;           // 分数
    int killNum = 0;         // 杀敌数
    int instance = 0;        // 距离
    int diamond_c = 0;       // 水晶钻石数量
    int diamond_y = 0;       // 黄钻石数量
    int diamond_r = 0;       // 红钻石数量
    
    /** UI元素 **/
    CCLabelTTF* labelScores;       // 分数标签
    CCLabelTTF* labelDistance;     // 距离标签
    CCLabelTTF* labelKillCount;    // 杀敌数标签
    CCLabelTTF* labelDiamond;      // 水晶钻石标签
    CCLabelTTF* labelDiamond1;     // 黄钻石标签
    CCLabelTTF* labelDiamond2;     // 红钻石标签
    CCLabelTTF* labelPlayerHP;     // 主机血量
    CCLabelTTF* labelPlayerAsHP;   // 辅机血量
    CCLabelTTF* labelBossHP;       // boss血量
    
    //飞机
    Plane *player = NULL;
    PlaneAs *playerAs = NULL;
    //boss
    Demon *demon = NULL;
    
    // 游戏模式
    GAME_TYPE gameType;
    // 存放敌怪的数组
    CCArray *arrayEnemy;
    // 子弹数组
    CCArray *arrayBullet;
    
    /** 工厂函数 **/
    void createBullet();
    void createAsBullet();
    void createEnemy();
    
    /** 工具函数 **/
    // UI初始化
    void initUI();
    // 游戏结算
    void dataStore();
    //显示游戏结束画面
    void showGameOver();
    //提示
    void showWarn();
    void hideWarn();
    //加分
    void addScore(float _value);
    //加杀敌数
    void addKillCount(float _value);
    //计算两点之间距离
    float Distance(CCPoint point1,CCPoint point2);

    
    /** 回调函数 **/
    //拖动事件
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    //暂停游戏
    void pauseGame();
    //继续游戏
    void resumeGame();
    //返回主菜单
    void goHome();
    
    //析构函数
    virtual ~Game();
};
#endif /* defined(________Game__) */
