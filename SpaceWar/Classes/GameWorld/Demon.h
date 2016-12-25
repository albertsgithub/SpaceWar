//
//  Demon.h
//  SpaceWar
//
//  Created by Xinhou Jiang on 23/12/16.
//
//

#ifndef ________Demon__
#define ________Demon__
#include "cocos2d.h"
using namespace cocos2d;

class Demon : public CCSprite {
    
    void bossInit(const char* fileName,int type);
    CCAnimate *createAnimate(int type);
    
public:
    static Demon* createDemon(const char* fileName,int _type);
    //boss类型
    int type;
    //boss生命值
    int bossHp;
};

#endif /* defined(__SpaceWar__Demon__) */
