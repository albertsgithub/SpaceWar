//
//  Plane0.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 4/2/14.
//
//
#include "Plane0.h"
#include "Game.h"
#include "Enemy.h"
/**
 * 枚举tag
 */
enum tag
{
    tagPlayerAuxiliary,//辅机
};
/**
 * 辅机静态单例
 */
Plane0* Plane0::createPlayer(const char* fileName,int _hpMax,int _hp,float x,float y)
{
    Plane0* player0 = new Plane0();
    if(player0 && player0->initWithFile(fileName))
    {
        player0->autorelease();
        player0->playerInit(fileName,_hpMax,_hp,x,y);
        return player0;
    }
    CC_SAFE_DELETE(player0);
    return NULL;
}
/**
 * 重载主机碰撞检测函数
 */
void Plane0::collideWithEnemy()
{
    if(isStrong)
        return;
    hp--;
    if(hp<=0)
    {
        Game::sharedWorld()->plane0IsExist=false;
        this->setVisible(false);
        SimpleAudioEngine::sharedEngine()->playEffect("plane0.wav");
        this->unscheduleUpdate();
        //爆炸离子
        auto boomparticle= CCParticleExplosion::create();
        boomparticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("particleTexture.png"));
        boomparticle->setPosition(this->getPosition());
        boomparticle->setAutoRemoveOnFinish(true);
    }
    else
    {
        //无敌三秒
        Plane0::startStrong(3);
    }
}
/**
 * 主机已经死亡
 */
void Plane0::playerWasDead()
{
    Game::sharedWorld()->plane0IsExist=false;
    removeChildByTag(tagPlayerAuxiliary);
    SimpleAudioEngine::sharedEngine()->playEffect("plane0.wav");
    this->unscheduleUpdate();
    //爆炸离子
    auto boomparticle= CCParticleExplosion::create();
    boomparticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("particleTexture.png"));
    boomparticle->setPosition(this->getPosition());
    boomparticle->setAutoRemoveOnFinish(true);
}
/**
 * 重载制作动画函数
 */
CCAnimate* Plane0::createAnimate(const char *fileName)
{
    auto animation_plane0 = CCAnimation::create();
    animation_plane0->addSpriteFrameWithFileName("plane_second.png");
    animation_plane0->addSpriteFrameWithFileName("plane_second.png");
    animation_plane0->addSpriteFrameWithFileName("plane_second.png");
    animation_plane0->addSpriteFrameWithFileName("plane_second.png");
    animation_plane0->addSpriteFrameWithFileName("plane_second.png");
    animation_plane0->setDelayPerUnit(0.03f);
    animation_plane0->setLoops(-1);
    animation_plane0->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_plane0);
    return animate_wellcome;
}
