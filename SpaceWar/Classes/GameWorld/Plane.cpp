//
//  Plane.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
#include "Plane.h"
#include "Bullet.h"
#include "Game.h"
#include "Enemy.h"
#include "Tool.h"
#include "SimpleAudioEngine.h"
/**
 * 枚举tag
 */
//enum tag
//{
//    tagBoss1,//boss1
//    tagPlayerMajor,//主机
//    tagPlayerAuxiliary,//辅机
//};
/**
 *  主机静态单例
 *
 *  @param fileName 贴图资源名
 *  @param _hpMax   最大血量
 *  @param _hp      血量
 *  @param x        起始坐标 x
 *  @param y        起始坐标 y
 *
 *  @return 返回初始化好的主机
 */
Plane* Plane::createPlayer(const char* fileName,int _hpMax,int _hp,float x,float y)
{
    Plane* player = new Plane();
    if(player && player->initWithFile(fileName))
    {
        player->autorelease();
        player->playerInit(fileName,_hpMax,_hp,x,y);
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}
/**
 *  初始化主机
 *
 *  @param fileName 贴图资源名
 *  @param _hpMax   最大血量
 *  @param _hp      血量
 *  @param x        起始坐标 x
 *  @param y        起始坐标 y
 */
void Plane::playerInit(const char* fileName,int _hpMax,int _hp,float x,float y) {
    //主机播放帧动画
    this->runAction(createAnimate(fileName));
    //添加无敌状态的保护罩
    sp_star = CCSprite::create("game_protect.png");
    sp_star->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2+10));
    sp_star->setVisible(false);
    this->addChild(sp_star);
    //初始化主角出场动作
    //出场塞倍儿曲线
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 =ccp(ScreenWidth, ScreenHeight);
    bezier2.controlPoint_2 =ccp(0,0);
    bezier2.endPosition =ccp(x, y);
    //塞贝儿曲线运动
    CCFiniteTimeAction *action_bezier2 = CCBezierTo::create(2, bezier2);
    this->setPosition(ccp(ScreenWidth/2, ScreenHeight*2));
    this->runAction(action_bezier2);
    //初始化主角状态参数
    //初始化血量上限
    hpMax =_hpMax;
    //初始化当前血量
    hp=_hp;
    show=true;
    //检测碰撞、吃道具的更新
    this->scheduleUpdate();
}

/**
 * 系统帧更新，检测与敌机碰撞
 */
void Plane::update(float time) {
    //检测与boss碰撞
    Demon* theBoss = Game::sharedWorld()->demon;
    if (theBoss && theBoss->boundingBox().intersectsRect(this->boundingBox())) {
        this->collideWithEnemy();
        theBoss->bossHp--;
    }
    //检测与敌机碰撞
    CCArray * array = Game::sharedWorld()->arrayEnemy;
    for (int i =0; i<array->count(); i++) {
        Enemy* enemy = (Enemy*)array->objectAtIndex(i);
        if (enemy->boundingBox().intersectsRect(this->boundingBox())) {
            //从敌人数组将被攻击的敌怪删除
            array->removeObject(enemy);
            Game::sharedWorld()->removeChild(enemy, true);
            this->collideWithEnemy();
        }
    }
}

/**
 *碰撞处理函数
 */
void Plane::collideWithEnemy() {
    if(isStrong) return;
    //手机振动
    CocosDenshion::SimpleAudioEngine::sharedEngine()->vibrate();
    hp--;
    if(hp <= 0) {
        if (Game::sharedWorld()->playerAs){
            Game::sharedWorld()->playerAs->removeFromParent();
            Game::sharedWorld()->playerAs = NULL;
        }
        //爆炸
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("plane.wav");
        CCParticleSystemQuad * particle11 = CCParticleSystemQuad::create("particle_plane_boom.plist");
        particle11->setPosition(this->getPosition());
        particle11->setAutoRemoveOnFinish(true);
        Game::sharedWorld()->addChild(particle11);
        
        this->removeFromParent();
        Game::sharedWorld()->player = NULL;
        
        //调用失败界面
        Game::sharedWorld()->showGameOver();
        this->unscheduleUpdate();
    }else {
        //碰撞后没死保护5s
        startStrong(5);
    }
}

/**
 * 制作主机动画
 */
CCAnimate* Plane::createAnimate(const char* fileName) {
    auto animation_plane = CCAnimation::create();
    for (int i = 1; i <= 5; i++) {
        CCString *filename = CCString::create("");
        filename->initWithFormat("menu_plane_left%d.png", i);
        animation_plane->addSpriteFrameWithFileName(filename->getCString());
    }
    animation_plane->setDelayPerUnit(0.03f);
    animation_plane->setLoops(-1);
    animation_plane->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_plane);
    return animate_wellcome;
}

/**
 * 开始无敌状态
 */
void Plane::startStrong(float strongTime) {
    isStrong=true;
    //显示无敌标志
    sp_star->setVisible(true);
    //闪烁
    this->schedule(schedule_selector(Plane::shine), 0.05, -1, 0);
    //三秒后结束无敌状态
    this->schedule(schedule_selector(Plane::endStrong), 1, 1, strongTime);
}

/**
 * 结束无敌
 */
void Plane::endStrong() {
    //隐藏无敌标志
    sp_star->setVisible(false);
    this->unschedule(schedule_selector(Plane::shine));
    this->setVisible(true);
    isStrong=false;
    this->unschedule(schedule_selector(Plane::endStrong));
}

/**
 * 无敌时的闪烁
 */
void Plane::shine() {
    if (show==true) {
        this->setVisible(false);
        show=false;
    }else {
        this->setVisible(true);
        show=true;
    }
}
