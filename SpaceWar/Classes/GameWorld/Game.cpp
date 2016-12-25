//
//  Game.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Game.h"
#include "SimpleAudioEngine.h"
#include <iostream>
using namespace std;

enum tag_game
{
    tagCallBack,
    tagWarn,
    tagColorLayer
};

//转换成string类型
template<typename T>
string Convert2String(const T &value)
{
    stringstream ss;
    ss << value;
    return ss.str();
}
// 游戏静态单例
static Game * game;

//游戏场景单例
Game * Game::sharedWorld()
{
    if(game)
        return game;
    return NULL;
}

CCScene* Game::scene()
{
    CCScene *scene = CCScene::create();
    Game *layer = Game::create();
    scene->addChild(layer);
    return scene;
}

/**
 * 游戏画面初始化
 */
bool Game::init()
{
    if (!CCLayer::init())
        return false;
    // 游戏场景实例
    game = this;
    // 播放游戏中的音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_bg_music.mp3",true);
    
    //如果是单机模式让辅机直接处于死亡状态,不产生子弹
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("choosedModel",true)) {
        gameType = GAME_DOUBLE;
    }else{
        gameType = GAME_SINGLE;
    }
    
    arrayEnemy = CCArray::create();     //初始化敌人数组
    CC_SAFE_RETAIN(arrayEnemy);         //增加敌人数组的一次引用
    
    // UI
    initUI();
    
    // 根据游戏模式添加玩家
    if (gameType == GAME_DOUBLE) {
        //精灵贴图、最大血量、初始化血量、初始位置
        player=Plane::createPlayer("plane_one.png",5,5,ScreenWidth/3,100);
        addChild(player,0);
        playerAs=PlaneAs::createPlayer("hero_purple1.png",5,5,ScreenWidth/3*2, 100);
        addChild(playerAs,0);
    }else{
        //精灵贴图、最大血量、初始化血量、初始位置
        player=Plane::createPlayer("plane_second.png",15,15,ScreenWidth/2,100);
        addChild(player,0);
    }
    
    //开启多触点监听
    setTouchEnabled(true);
    
    // 计时器
    this->scheduleUpdate();
    // 每1秒产生一次敌机,无限重复，第一次延迟5s
    this->schedule(schedule_selector(Game::createEnemy), 1,-1,5);
    // 每0.2秒产生一次子弹，无限重复，第一次延迟3s
    this->schedule(schedule_selector(Game::createBullet), 0.2,-1,3);
    this->schedule(schedule_selector(Game::createBullet0), 0.3, -1, 3);
    return true;
}

/**
 * 更新不断产生敌机
 */
void Game::createEnemy()
{
    Enemy *enemy = NULL;
    enemy->autoCreateEnemy();
}

/**
 * 产生主机子弹
 */
void Game::createBullet()
{
    if(!player) return;
    addChild(Bullet::createBullet("bullet_red.png",0,30,ccp(player->getPosition().x+13,player->getPosition().y)));
    addChild(Bullet::createBullet("bullet_red.png",0,30,ccp(player->getPosition().x-13,player->getPosition().y)));
    //子弹音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effect_bullet.mp3");
}

/**
 * 产生辅机子弹
 */
void Game::createBullet0()
{
    if(!playerAs) return;
    //子弹参数：图片-x速度-y速度-初始位置
    addChild(Bullet::createBullet("bullet_blue.png",5,15,ccp(playerAs->getPosition().x+5,playerAs->getPosition().y+20)));
    addChild(Bullet::createBullet("bullet_blue.png",-5,15,ccp(playerAs->getPosition().x-5,playerAs->getPosition().y+20)));
    addChild(Bullet::createBullet("bullet_blue.png",0,10,ccp(playerAs->getPosition().x-10,playerAs->getPosition().y+20)));
    addChild(Bullet::createBullet("bullet_blue.png",0,10,ccp(playerAs->getPosition().x+10,playerAs->getPosition().y+20)));
}

/**
 * 提示
 */
void Game::showWarn()
{
    //击杀boss提示
    string warn_str="YOU HAVE KILLED THE BOSS!";
    CCLabelTTF *message = CCLabelTTF::create(warn_str.c_str(), font1, 30);
    message->setPosition(ccp(ScreenWidth/2, ScreenHeight/3*2));
    message->setColor(ccc3(255, 0, 0));
    message->setTag(tagWarn);
    addChild(message);
}

/**
 * 按帧刷新
 */
void Game::update(float time)
{
    // 1.设置boss的登场
    //当到达一定距离并且当前不存在boss时，添加boss
    //1.boss1
    if(instance>1000 && instance<2000 && !demon)
    {
        demon = Demon::createDemon("boss.png",0);
        addChild(demon,0);
    }
    //2.boss2
    if(instance>4000 && instance<6000 && !demon)
    {
        demon = Demon::createDemon("menu_plane_left1.png",1);
        addChild(demon,0);
    }
    //3.boss3
    if(instance>7000 && !demon)
    {
        demon = Demon::createDemon("purple1.png",2);
        addChild(demon,0);
    }
    
    // 1.更新钻石数目
    //水晶钻
    string strDiamond1=Convert2String(diamond_c);
    labelDiamond->setString(strDiamond1.c_str());
    //黄钻
    string strDiamond=Convert2String(diamond_y);
    labelDiamond1->setString(strDiamond.c_str());
    //红钻
    string strDiamond2=Convert2String(diamond_r);
    labelDiamond2->setString(strDiamond2.c_str());
    
    // 2.更新血量
    //boss
    if (demon) {
        string strBossHp=Convert2String(demon->bossHp-1);
        Game::sharedWorld()->labelBossHP->setString(strBossHp.c_str());
    }
    //plane
    if (player) {
        string strPlaneHp=Convert2String(player->hp-1);
        Game::sharedWorld()->labelPlayerHP->setString(strPlaneHp.c_str());
    }
    //planeas
    if (playerAs) {
        string strPlane0Hp=Convert2String(playerAs->hp-1);
        Game::sharedWorld()->labelPlayerAsHP->setString(strPlane0Hp.c_str());
    }
    
    //200m后隐藏提示
    if (instance>record+200){
        Game::sharedWorld()->getChildByTag(tagWarn)->setVisible(false);
        record = instance + 100000;
    }
    
    // 3.更新距离
    instance++;
    std::string strInstance=Convert2String(instance);
    labelDistance->setString(strInstance.c_str());
}

/**
 * 添加积分分数
 */
void Game::addScore(float _value)
{
    score+=_value;
    std::string strScore=Convert2String(score);
    labelScores->setString(strScore.c_str());
}

/**
 * 添加杀敌数
 */
void Game::addKillCount(float _value)
{
    killNum+=_value;
    std::string strKillNum=Convert2String(killNum);
    labelKillCount->setString(strKillNum.c_str());
}

/**
 * 显示数据信息
 */
void Game::initUI()
{
    /*
     // 随机初始化地图
     char *mapname;
     string map_green = "map_green.png";
     string map_yello = "map_yello.png";
     string map_night = "map_night.png";
     int maptag = CCRANDOM_0_1()*10;
     if (maptag<5)
     strlcpy(mapname, map_green.c_str(), map_green.length()+1);
     else if(maptag<7)
     strlcpy(mapname, map_yello.c_str(), map_yello.length()+1);
     else
     strlcpy(mapname, map_night.c_str(), map_night.length()+1);
     */
    Map * map = Map::createMap("map_green.png",3);
    addChild(map);
    
    //云层
    //Map * clouds = Map::createMap("clouds.png",1);
    //addChild(clouds);
    
    //离子
    CCParticleSystemQuad * light = CCParticleSystemQuad::create("particle_color.plist");
    light->setPosition(ScreenWidth/2,ScreenHeight/1.5);
    addChild(light);

    
    // UI层级
    int UIZOrder = 100;
    // 0.血量
    //boss
    labelBossHP = CCLabelTTF::create("", font1, 30);
    labelBossHP->setPosition(ccp(30,ScreenHeight-250));
    labelBossHP->setColor(ccc3(255, 0, 0));
    this->addChild(labelBossHP,UIZOrder);
    //plane
    labelPlayerHP = CCLabelTTF::create("", font1, 30);
    labelPlayerHP->setPosition(ccp(30,ScreenHeight-300));
    labelPlayerHP->setColor(ccc3(0, 0, 255));
    this->addChild(labelPlayerHP,UIZOrder);
    //planeas
    labelPlayerAsHP = CCLabelTTF::create("", font1, 30);
    labelPlayerAsHP->setPosition(ccp(30,ScreenHeight-350));
    labelPlayerAsHP->setColor(ccc3(0,225, 0));
    this->addChild(labelPlayerAsHP,UIZOrder);
    
    // 1.分数
    CCLabelTTF * label = CCLabelTTF::create("分数:", font1, 20);
    label->setPosition(ccp(30,ScreenHeight-52));
    this->addChild(label,10);
    std::string strScore=Convert2String(score);
    labelScores = CCLabelTTF::create(strScore.c_str(), font1, 20);
    labelScores->setPosition(ccp(110,ScreenHeight-52));
    labelScores->setColor(ccc3(255, 0, 255));
    this->addChild(labelScores,UIZOrder);
    
    // 2.杀敌人数
    CCLabelTTF* labelKill = CCLabelTTF::create("杀敌:", font1, 20);
    labelKill->setPosition(ccp(30,ScreenHeight-82));
    this->addChild(labelKill,10);
    std::string strKillCount=Convert2String(killNum);
    labelKillCount = CCLabelTTF::create(strKillCount.c_str(), font2, 20);
    labelKillCount->setPosition(ccp(110,ScreenHeight-82));
    labelKillCount->setColor(ccc3(255, 0, 255));
    this->addChild(labelKillCount,UIZOrder);
    
    // 3.距离
    CCLabelTTF* labelDis = CCLabelTTF::create("距离:", font1, 20);
    labelDis->setPosition(ccp(30,ScreenHeight-112));
    this->addChild(labelDis,10);
    std::string strDistance=Convert2String(instance);
    labelDistance = CCLabelTTF::create(strDistance.c_str(), font2, 20);
    labelDistance->setPosition(ccp(110,ScreenHeight-112));
    labelDistance->setColor(ccc3(255, 0, 255));
    this->addChild(labelDistance,UIZOrder);
    
    // 4.钻石
    CCSprite *diamond0 =CCSprite::create("diamond_crystal.png");
    diamond0->setPosition(ccp(30,ScreenHeight-142));
    diamond0->setScale(0.4);
    diamond0->setRotation(30);
    this->addChild(diamond0,UIZOrder);
    
    CCSprite *diamond1 =CCSprite::create("diamond_yellow.png");
    diamond1->setPosition(ccp(30,ScreenHeight-172));
    diamond1->setScale(0.4);
    diamond1->setRotation(30);
    this->addChild(diamond1,UIZOrder);
    
    CCSprite *diamond2 =CCSprite::create("diamond_red.png");
    diamond2->setPosition(ccp(30,ScreenHeight-202));
    diamond2->setScale(0.4);
    diamond2->setRotation(30);
    this->addChild(diamond2,UIZOrder);
    
    string strDiamond=Convert2String(diamond_c);
    labelDiamond = CCLabelTTF::create(strDiamond.c_str(), font2, 20);
    labelDiamond->setPosition(ccp(110,ScreenHeight-142));
    labelDiamond->setColor(ccc3(255, 0, 255));
    this->addChild(labelDiamond,UIZOrder);
    
    string strDiamond1=Convert2String(diamond_y);
    labelDiamond1 = CCLabelTTF::create(strDiamond1.c_str(), font2, 20);
    labelDiamond1->setPosition(ccp(110,ScreenHeight-172));
    labelDiamond1->setColor(ccc3(255, 0, 255));
    this->addChild(labelDiamond1,UIZOrder);
    
    string strDiamond2=Convert2String(diamond_r);
    labelDiamond2 = CCLabelTTF::create(strDiamond2.c_str(), font2, 20);
    labelDiamond2->setPosition(ccp(110,ScreenHeight-202));
    labelDiamond2->setColor(ccc3(255, 0, 255));
    this->addChild(labelDiamond2,UIZOrder);
    
    // 5.游戏操作
    // 结束游戏按钮
    CCMenuItemImage *stopButton=CCMenuItemImage::create("stop.png", "shadow.png", this, menu_selector(Game::goHome));
    stopButton->setPosition(ccp(ScreenWidth/3+50,ScreenHeight/2-100));
    
    // 暂停游戏按钮
    CCMenuItemImage *resumeButton=CCMenuItemImage::create("pause.png", "shadow.png", this, menu_selector(Game::pauseGame));
    resumeButton->setPosition(ccp(ScreenWidth/3+50,ScreenHeight/2-200));
    CCMenu* menu =CCMenu::create(stopButton,resumeButton,NULL);
    // 添加操作菜单，z轴最高
    addChild(menu,UIZOrder);

}

void Game::dataStore() {
    //存储最高分数
    int oldScore = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str());
    if(score > oldScore)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Convert2String(score));
        CCUserDefault::sharedUserDefault()->flush();
    }
    //存储最高杀敌数
    int oldKillNum = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_killNum","-1").c_str());
    if(killNum > oldKillNum)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("user_killNum", Convert2String(killNum));
        CCUserDefault::sharedUserDefault()->flush();
    }
    //存储最远距离
    int oldInstance = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_distance","-1").c_str());
    if(instance > oldInstance)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("user_distance", Convert2String(instance));
        CCUserDefault::sharedUserDefault()->flush();
    }
    //存储钻石数据
    int oldDiamond_cry = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_diamond_cry","0").c_str());
    CCUserDefault::sharedUserDefault()->setStringForKey("user_diamond_cry", Convert2String(oldDiamond_cry+diamond_c));
    CCUserDefault::sharedUserDefault()->flush();
    
    int oldDiamond_y = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_diamond_y","0").c_str());
    CCUserDefault::sharedUserDefault()->setStringForKey("user_diamond_y", Convert2String(oldDiamond_y+diamond_y));
    CCUserDefault::sharedUserDefault()->flush();
    
    int oldDiamond_r = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_diamond_r","0").c_str());
    CCUserDefault::sharedUserDefault()->setStringForKey("user_diamond_r", Convert2String(oldDiamond_r+diamond_r));
    CCUserDefault::sharedUserDefault()->flush();

}

void Game::showGameOver()
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 190), ScreenWidth, ScreenHeight);
    this->addChild(layer);
    
    CCSprite* sp = CCSprite::create("game_lost.png");
    sp->setPosition(ccp(ScreenWidth/2,ScreenHeight/2));
    layer->addChild(sp);
    
    CCLabelTTF* ttback =CCLabelTTF::create("返回", font1, 53);
    ttback->setColor(ccc3(0, 255, 255));
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback,this, menu_selector(Game::goHome));
    menuLabel->setPosition(ccp(0,-200));
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
    this->addChild(menu);
    //暂停游戏
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("end.mp3",false);
    CCDirector::sharedDirector()->pause();
    
    // 游戏结算
    dataStore();
}

/**
 * 暂停游戏
 */
void Game:: pauseGame()
{
    //按钮音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //游戏暂停
    CCDirector::sharedDirector()->pause();
    //暂停背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
    // 0.暂停界面灰色layer层
    CCLayerColor *pauseLayer = CCLayerColor::create(ccc4(0, 0, 0, 190),ScreenWidth,ScreenHeight);
    pauseLayer->setTag(tagCallBack);
    // 1.添加返回提示图片
    CCSprite *callback=CCSprite::create("callback.png");
    callback->setPosition(ccp(ScreenWidth/2,ScreenHeight/2));
    pauseLayer->addChild(callback,1);
    // 1.暂停返回按钮
    CCMenuItemImage *resumeButton=CCMenuItemImage::create("resume.png", "shadow.png", this, menu_selector(Game::resumeGame));
    CCMenu *menu =CCMenu::create(resumeButton,NULL);
    menu->setPosition(ccp(ScreenWidth/2,ScreenHeight/3));
    pauseLayer->addChild(menu);
    // 添加暂停界面
    addChild(pauseLayer,1);//1为z轴，默认为0，z轴大的覆盖z轴小的
}

/**
 * 继续游戏
 */
void Game:: resumeGame()
{
    //音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //移除暂停界面
    this->removeChildByTag(tagCallBack, true);
    //游戏继续
    CCDirector::sharedDirector()->resume();
    //继续背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

/**
 * 返回主菜单
 */
void Game::goHome()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    //切换到"菜单"场景
    CCDirector::sharedDirector()->replaceScene(Menu::scene());

}

/**
 * 计算两点之间的距离
 */
float Game::Distance(CCPoint point1,CCPoint point2)
{
    return sqrt(pow((point1.x-point2.x),2)+pow(point1.y-point2.y, 2));
}

/**
 * 用户手指进行移动或者拖拽
 */
void Game::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    //int c = pTouches->count();
    //cout<<"触点个数："<<c<<endl;
    if (!player) return;
    CCSetIterator iter = pTouches->begin();
    if(playerAs) {
    for (; iter !=pTouches->end(); iter++) {
        //获取两个飞机对象
        CCPoint point1=player->getPosition();
        CCPoint point2=playerAs->getPosition();
        CCTouch *pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        //根据触点与两个飞机之间的距离判断触控情况
        //首先触点与飞机必须足够近，不然用户并没有触碰到飞机
        //触点应该给相对较近的那个飞机
        if (pTouch->getID()==0)
        {
            if (Distance(location, point1)<Distance(location, point2)&&Distance(location, point1)<100.0) {
                player->setPosition(location);
            }
            else if(Distance(location, point2)<100.0)
                playerAs->setPosition(location);
        }
        else if (pTouch->getID()==1)
        {
            if (Distance(location, point2)<Distance(location, point1)&&Distance(location, point2)<100.0) {
                playerAs->setPosition(location);
            }
            else if(Distance(location, point1)<100.0)
                player->setPosition(location);
        }
    }
    }else{
        CCPoint point1=player->getPosition();
        CCTouch *pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        if (Distance(point1, location)<=player->getContentSize().width){
            player->setPosition(location);
        }
    }
}

/**
 * 析构函数
 */
Game::~Game(){
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    this->unscheduleUpdate();
    this->unscheduleAllSelectors();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CC_SAFE_RELEASE(arrayEnemy);
}
