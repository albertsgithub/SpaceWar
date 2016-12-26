//
//  PlaneAs.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 4/2/14.
//
//
#include "PlaneAs.h"
#include "Game.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"

/**
 * 辅机静态单例
 */
PlaneAs* PlaneAs::createPlayer(const char* fileName,int _hpMax,int _hp,float x,float y)
{
    PlaneAs* player0 = new PlaneAs();
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
void PlaneAs::collideWithEnemy()
{
    if(isStrong) return;
    hp--;
    if(hp <= 0)
    {
        // 爆炸离子
        auto boomparticle= CCParticleExplosion::create();
        boomparticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("particleTexture.png"));
        boomparticle->setPosition(this->getPosition());
        boomparticle->setAutoRemoveOnFinish(true);
        this->removeFromParent();
        Game::sharedWorld()->playerAs = NULL;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("PlaneAs.wav");
    }else
    {
        //无敌三秒
        PlaneAs::startStrong(3);
    }
}

/**
 * 重载制作动画函数
 */
CCAnimate* PlaneAs::createAnimate(const char *fileName) {
    auto animation_PlaneAs = CCAnimation::create();
    for (int i = 1; i <= 1; i++) {
        CCString *name = CCString::create("plane_second.png");
        //name->initWithFormat("menu_plane_left%d.png", i);
        animation_PlaneAs->addSpriteFrameWithFileName(name->getCString());
    }
    animation_PlaneAs->setDelayPerUnit(0.03f);
    animation_PlaneAs->setLoops(-1);
    animation_PlaneAs->setRestoreOriginalFrame(false);
    auto animate_wellcome = CCAnimate::create(animation_PlaneAs);
    return animate_wellcome;
}
