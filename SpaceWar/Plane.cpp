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
/**
 * 枚举tag
 */
enum tag
{
    tagProtect,//护罩
    tagBoss1,//boss1
    tagPlayerMajor,//主机
    tagPlayerAuxiliary,//辅机
};
/**
 * 主机静态单例
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
 * 初始化主机，参数为：贴图资源名，最大血量，血量，起始坐标
 */
void Plane::playerInit(const char* fileName,int _hpMax,int _hp,float x,float y)
{
    this->runAction(createAnimate(fileName));
    //添加无敌状态的保护罩
    CCSprite *sp_star = CCSprite::create("环.png");
    this->addChild(sp_star);
    sp_star->setPosition(ccp(this->getPositionX()+this->getContentSize().width/2+10,this->getPositionY()+this->getContentSize().height/2+10));
    sp_star->setVisible(false);
    sp_star->setTag(tagProtect);
    //初始化主角出场动作
    ccBezierConfig bezier2;//出场塞倍儿曲线
    bezier2.controlPoint_1 =ccp(ScreenWidth, ScreenHeight);
    bezier2.controlPoint_2 =ccp(0,0);
    bezier2.endPosition =ccp(x, y);
    CCFiniteTimeAction *action_bezier2 = CCBezierTo::create(2, bezier2);//塞贝儿曲线运动
    this->setPosition(ccp(ScreenWidth/2, ScreenHeight*2));
    this->runAction(action_bezier2);
    //初始化主角状态参数
    hpMax =_hpMax;//初始化血量上限
    hp=_hp;//初始化当前血量
    show=true;
    this->scheduleUpdate();//检测碰撞、吃道具的更新
}
/**
 * 系统帧更新，检测与敌机碰撞
 */
void Plane::update(float time)
{
    //检测与boss碰撞
    Boss* theBoss=(Boss*)Game::sharedWorld()->getChildByTag(tagBoss1);
    if (Game::sharedWorld()->bossIsExist&&theBoss->boundingBox().intersectsRect(this->boundingBox()))
    {
        this->collideWithEnemy();
        theBoss->bossHp--;
    }
    //检测与敌机碰撞
    CCArray * array = Game::sharedWorld()->arrayEnemy;
    for (int i =0; i<array->count(); i++)
    {
        Enemy* enemy = (Enemy*)array->objectAtIndex(i);
        if (enemy->boundingBox().intersectsRect(this->boundingBox()))
        {
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
void Plane::collideWithEnemy()
{
    if(isStrong||Game::sharedWorld()->planeIsExist==false)
        return;
        //手机振动
        //SimpleAudioEngine::sharedEngine()->vibrate();
    hp--;
    if(hp<=0)
    {
        Plane0 *plane0_temp=(Plane0*)Game::sharedWorld()->getChildByTag(tagPlayerAuxiliary);
        if (CCUserDefault::sharedUserDefault()->getBoolForKey("choosedModel",true)){
            plane0_temp->playerWasDead();
        }
        Game::sharedWorld()->planeIsExist=false;
        //爆炸
        SimpleAudioEngine::sharedEngine()->playEffect("plane.wav");
        CCParticleSystemQuad * particle11 = CCParticleSystemQuad::create("主机爆炸.plist");
        particle11->setPosition(this->getPosition());//主机位置
        particle11->setAutoRemoveOnFinish(true);//自动释放
        Game::sharedWorld()->addChild(particle11);
        removeChildByTag(tagPlayerMajor);
        //调用失败界面
        Game::sharedWorld()->lostGame();
        this->unscheduleUpdate();
    }
    else
    {
        Plane::startStrong(5);//碰撞后没死保护5s
    }
}
/**
 * 制作主机动画
 */
CCAnimate* Plane::createAnimate(const char* fileName)
{
    auto animation_plane = CCAnimation::create();
    animation_plane->addSpriteFrameWithFileName("menu_plane_left1.png");
    animation_plane->addSpriteFrameWithFileName("menu_plane_left2.png");
    animation_plane->addSpriteFrameWithFileName("menu_plane_left3.png");
    animation_plane->addSpriteFrameWithFileName("menu_plane_left4.png");
    animation_plane->addSpriteFrameWithFileName("menu_plane_left5.png");
    animation_plane->setDelayPerUnit(0.03f);
    animation_plane->setLoops(-1);
    animation_plane->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_plane);
    return animate_wellcome;
}
/**
 * 开始无敌状态
 */
void Plane::startStrong(float strongTime)
{
    isStrong=true;
    //auto sp_temp = getChildByTag(tag_protect);
    //sp_temp->setVisible(true);//显示无敌标志
    this->schedule(schedule_selector(Plane::shine), 0.05, -1, 0);//闪烁
    this->schedule(schedule_selector(Plane::endStrong), 1, 1, strongTime);//三秒后结束无敌状态
}
/**
 * 结束无敌
 */
void Plane::endStrong()
{
    //auto sp_temp1 =getChildByTag(tag_protect);
    //sp_temp1->setVisible(false);//隐藏无敌标志
    this->unschedule(schedule_selector(Plane::shine));
    this->setVisible(true);
    isStrong=false;
    this->unschedule(schedule_selector(Plane::endStrong));
}
/**
 * 无敌时的闪烁
 */
void Plane::shine()
{
    if (show==true) {
        this->setVisible(false);
        show=false;
    }
    else
    {
        this->setVisible(true);
        show=true;
    }
}