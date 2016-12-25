//
//  Tool.cpp
//  PlaneDemo
//
//  Created by mac on 14-3-31.
//
//
#include "Tool.h"
#include "Game.h"
/**
 * 道具静态单例
 */
Tool* Tool::createTool(const char *fileName, int _type,CCPoint _position)
{
    Tool* tool=new Tool();
    if(tool && tool->initWithFile(fileName)){
        tool->autorelease();
        tool->toolInit(_type,_position);
        return tool;
    }
    CC_SAFE_DELETE(tool);
    return NULL;
}
/**
 * 道具初始化
 */
void Tool::toolInit(int _type,CCPoint _position)
{
    this->setPosition(_position);
    this->type = _type;
    this->scheduleUpdate();
    //道具下落方式(CCMoveTo参数：动作完成时间，目的坐标)
    CCMoveTo *action_toolDown = CCMoveTo::create(2, ccp(this->getPositionX(), -100));
    CCRotateTo *action_toolRotate =CCRotateTo::create(3, 180.0f);//旋转
    this->runAction(CCSpawn::create(action_toolDown,action_toolRotate,NULL));
}
/**
 * 自动产生道具
 */
void Tool::autoCreateTool(CCPoint _enemyPosition)
{
    Tool *tool1=NULL;
    int percent = CCRANDOM_0_1()*100;
    if (percent<90)
    {

        if(percent<50)
        tool1 = Tool::createTool("diamond_yellow.png", 1, _enemyPosition);
        
        else if(percent>=50&&percent<85)
        tool1 = Tool::createTool("diamond_crystal.png", 2, _enemyPosition);

        else if (percent>=85)
        tool1 = Tool::createTool("diamond_red.png", 3, _enemyPosition);
    }
    else if (percent>=90&&percent<97)
    {
        tool1 = Tool::createTool("HP.png", 4, _enemyPosition);
    }
    else
    {
        tool1 = Tool::createTool("protect.png", 5, _enemyPosition);
    }
    tool1->setScale(0.6);
    Game::sharedWorld()->addChild(tool1);
}
/**
 * 道具下落
 */
void Tool::update(float time)
{
    Tool::beGeted();
    if (this->getPositionY()<(-this->getContentSize().height))
        Game::sharedWorld()->removeChild(this,true);
}
/**
 * 检测道具与主角碰撞
 */
void Tool::beGeted()
{
    Plane *planex = Game::sharedWorld()->player;
    if (!planex) return;
    if (this->boundingBox().intersectsRect(planex->boundingBox()))
    {
        switch (this->type)
        {
            case 1:
                Game::sharedWorld()->diamond_y++;
                break;
            case 2:
                Game::sharedWorld()->diamond_c++;
                break;
            case 3:
                Game::sharedWorld()->diamond_r++;
                break;
            case 4:
                planex->hp++;
                break;
            case 5:
                //秘密武器(暂定无敌状态5s)
                planex->startStrong(5);
                break;
            default:
                break;
        }
    this->removeFromParent();//移除当前道具
    }
}
