//
//  Bullet.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Bullet.h"
#include "Game.h"
#include "Enemy.h"
#include "Tool.h"
#include "SimpleAudioEngine.h"

/*子弹实例化函数，惨数：贴图资源，x轴水平速度，y轴竖直速度，出现位置*/
Bullet* Bullet::createBullet(const char* _fileName,float _speedx,float _speedy,CCPoint _position) {
    Bullet* bullet = new Bullet();
    if(bullet && bullet->initWithFile(_fileName))
    {
        bullet->bulletInit(_speedx,_speedy,_position);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}

void Bullet::bulletInit(float _speedx,float _speedy,CCPoint _position) {
    speedx = _speedx;
    speedy = _speedy;
    this->setPosition(_position);
    // 碰撞检测
    this->scheduleUpdate();
    // 移动回调
    this->schedule(schedule_selector(Bullet::move), 0.01);
}

void Bullet::move() {
    // 子弹移动
    this->setPosition(ccpAdd(this->getPosition(), ccp(speedx,speedy)));
    
    //子弹超出屏幕则移除
    if (this->getPositionY() >= ScreenHeight) {
        this->removeFromParent();
        Game::sharedWorld()->arrayBullet->removeObject(this);
    }
}

void Bullet::update(float time)
{
    //子弹与敌机相撞
    CCArray * array = Game::sharedWorld()->arrayEnemy;
    for (int i =0; i<array->count(); i++)
    {
        Enemy* enemy = (Enemy*)array->objectAtIndex(i);
        Tool * tool2=NULL;
        //只有与特定敌机相撞并且在屏幕内才算击中敌机
        if (enemy->boundingBox().intersectsRect(this->boundingBox())&&this->getPositionY()<ScreenHeight)
            {
                if(enemy->type!=2)
                {
                    Game::sharedWorld()->removeChild(this, true);
                    //爆炸粒子效果
                    CCParticleSystemQuad * particle = CCParticleSystemQuad::create("particle_boom.plist");
                    particle->setPosition(enemy->getPosition());//敌机位置
                    particle->setAutoRemoveOnFinish(true);//自动释放
                    Game::sharedWorld()->addChild(particle);
                    if (enemy->enemyHp==0)
                    {
                        //爆炸音效
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effect_boom.mp3");
                        //一定几率产生道具
                        int randomTool=CCRANDOM_0_1()*10;
                        if (randomTool>5)
                            tool2->autoCreateTool(enemy->getPosition());
                        //增加分数
                        Game::sharedWorld()-> addScore(enemy->scoreValue);
                        //添加杀人数
                        Game::sharedWorld()->addKillCount(1);
                        //从敌人数组将被攻击的敌怪删除
                        array->removeObject(enemy);
                        //删除敌怪
                        Game::sharedWorld()->removeChild(enemy, true);
                    }
                    else
                    {
                        enemy->enemyHp--;
                    }
                }

            }
    }
}
