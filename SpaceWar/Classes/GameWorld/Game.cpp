//
//  Game.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Game.h"

/**
 * 枚举
 */
enum tag
{
    tagCallBack
};

/**
 * 游戏静态单例
 */
static Game * game;

/**
 * 游戏场景单例get函数
 */
Game * Game::sharedWorld()
{
    if(game)
        return game;
    return NULL;
}

/**
 * 创建一个游戏场景
 */
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
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_bg_music.mp3",true);
    
    // 初始化游戏数据
    score = 0;        //初始化当前积分分数
    diamond_y = 0;    //黄 初始化当前钻石数目
    diamond_c = 0;    //水晶
    diamond_r = 0;    //红
    instance = 0;     //初始化当前距离
    record = 100000;  //距离存储器
    killNum = 0;      //初始化杀敌数
    
    //如果是单机模式让辅机直接处于死亡状态,不产生子弹
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("choosedModel",true)) {
        plane0IsExist = true;
    }else{
        plane0IsExist = false;
    }
    
    planeIsExist = true;                //初始化飞机状态
    bossIsExist = false;                //初始化boss不存在
    arrayEnemy = CCArray::create();     //初始化敌人数组
    
    CC_SAFE_RETAIN(arrayEnemy);         //增加敌人数组的一次引用
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

    //主机，根据辅机存不存在设置初始化出场位置
    if (plane0IsExist) {
        //精灵贴图、最大血量、初始化血量、初始位置
        playerMajor=Plane::createPlayer("plane_one.png",10,10,ScreenWidth/3,100);
        addChild(playerMajor,0);
    }else{
        //精灵贴图、最大血量、初始化血量、初始位置
        playerMajor=Plane::createPlayer("plane_second.png",15,15,ScreenWidth/2,100);
        addChild(playerMajor,0);
    }
    
    //辅助机
    if (plane0IsExist) {
        playerAuxiliary=Plane0::createPlayer("hero_purple1.png",5,5,ScreenWidth/3*2, 100);
        addChild(playerAuxiliary,0);
    }

    //开启多触点监听
    setTouchEnabled(true);
    //显示杀敌、分数等信息
    showMessage();
    //游戏中的操作(暂停、结束)
    gameOperation();

    // 计时器
    this->scheduleUpdate();
    // 每1秒产生一次敌机,无限重复，第一次延迟5s
    this->schedule(schedule_selector(Game::createEnemy), 1,-1,5);
    // 每0.2秒产生一次子弹，无限重复，第一次延迟3s
    this->schedule(schedule_selector(Game::createBullet), 0.2,-1,3);
    this->schedule(schedule_selector(Game::createBullet0), 0.3, -1, 3);
    // 更新距离,0.1s更新一次
    this->schedule(schedule_selector(Game::setDistance), 0.1);

    return true;
}

/**
 * 更新不断产生敌机
 */
void Game::createEnemy()
{
    Enemy *enemy0=NULL;
    enemy0->autoCreateEnemy();
}

/**
 * 产生主机子弹
 */
void Game::createBullet()
{
    if(planeIsExist)
    {
        addChild(Bullet::createBullet("bullet_red.png",0,30,ccp(playerMajor->getPosition().x+13,playerMajor->getPosition().y)
                                    ));
        addChild(Bullet::createBullet("bullet_red.png",0,30,ccp(playerMajor->getPosition().x-13,playerMajor->getPosition().y)
                                    ));
        //子弹音效
        SimpleAudioEngine::sharedEngine()->playEffect("effect_bullet.mp3");
    }
   }

/**
 * 产生辅机子弹
 */
void Game::createBullet0()
{
    if(!Game::sharedWorld()->plane0IsExist) return;
    //子弹参数：图片-x速度-y速度-初始位置
    addChild(Bullet::createBullet("bullet_blue.png",5,15,ccp(playerAuxiliary->getPosition().x+5,playerAuxiliary->getPosition().y+20)));
    addChild(Bullet::createBullet("bullet_blue.png",-5,15,ccp(playerAuxiliary->getPosition().x-5,playerAuxiliary->getPosition().y+20)));
    addChild(Bullet::createBullet("bullet_blue.png",0,10,ccp(playerAuxiliary->getPosition().x-10,playerAuxiliary->getPosition().y+20)));
    addChild(Bullet::createBullet("bullet_blue.png",0,10,ccp(playerAuxiliary->getPosition().x+10,playerAuxiliary->getPosition().y+20)));
}

/**
 * 隐藏提示
 */
void Game::showWarn()
{
    //击杀boss提示
    string warn_str="YOU HAVE KILLED THE BOSS!";
    char *warn;
    strlcpy(warn, warn_str.c_str(),warn_str.length()+1);
    CCLabelTTF *message=CCLabelTTF::create(warn, font1, 30);
    message->setPosition(ccp(ScreenWidth/2, ScreenHeight/3*2));
    message->setColor(ccc3(255, 0, 0));
    message->setTag(555);
    addChild(message);
}

/**
 * 按帧刷新
 */
void Game::update(float time)
{
    //设置boss的登场
    //当到达一定距离并且当前不存在boss时，添加boss
//    //1.boss1
//    if(instance>1000&&instance<2000&&bossIsExist==false)
//    {
//    boss=Boss::createBoss("boss.png",0);
//    addChild(boss,0);
//    bossIsExist=true;
//    }
//    //2.boss2
//    if(instance>4000&&instance<6000&&bossIsExist==false)
//    {
//        boss=Boss::createBoss("menu_plane_left1.png",1);
//        addChild(boss,0);
//        bossIsExist=true;
//    }
//    //3.boss3
//    if(instance>7000&&bossIsExist==false)
//    {
//        boss=Boss::createBoss("purple1.png",2);
//        addChild(boss,0);
//        bossIsExist=true;
//    }
    //更新钻石数目
    //水晶钻
    string strDiamond1=Convert2String(diamond_c);
    labelDiamond->setString(strDiamond1.c_str());
    //黄钻
    string strDiamond=Convert2String(diamond_y);
    labelDiamond1->setString(strDiamond.c_str());
    //红钻
    string strDiamond2=Convert2String(diamond_r);
    labelDiamond2->setString(strDiamond2.c_str());
    //更新血量
    //boss
//    if (bossIsExist) {
//        string strBossHp=Convert2String(boss->bossHp-1);
//        CCLabelTTF* ttfa1 = (CCLabelTTF*)Game::sharedWorld()->getChildByTag(111);
//        ttfa1->setString(strBossHp.c_str());
//    }
    //plane
    if (planeIsExist) {
        string strPlaneHp=Convert2String(playerMajor->hp-1);
        CCLabelTTF* ttfb2 = (CCLabelTTF*)Game::sharedWorld()->getChildByTag(222);
        ttfb2->setString(strPlaneHp.c_str());
    }
    //plane0
    if (plane0IsExist) {
        string strPlane0Hp=Convert2String(playerAuxiliary->hp-1);
        CCLabelTTF* ttfc3 =(CCLabelTTF*)Game::sharedWorld()->getChildByTag(333);
        ttfc3->setString(strPlane0Hp.c_str());
    }
    //200m后隐藏提示
    if (instance>record+200){
        Game::sharedWorld()->getChildByTag(555)->setVisible(false);
        record=100000;
    }
}

/**
 * 刷新距离
 */
void Game::setDistance()
{
    instance+=10;
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
void Game::showMessage()
{
    //显示血量
    //boss
//    if (bossIsExist) {
//        string strBossHp=Convert2String(boss->bossHp);
//        CCLabelTTF* labelBossHp = CCLabelTTF::create(strBossHp.c_str(), font1, 30);
//        labelBossHp->setPosition(ccp(30,ScreenHeight-250));
//        labelBossHp->setColor(ccc3(255, 0, 0));
//        this->addChild(labelBossHp,10,111);
//    }
    //plane
    if (planeIsExist) {
        string strPlaneHp=Convert2String(playerMajor->hp);
        CCLabelTTF* labelPlaneHp = CCLabelTTF::create(strPlaneHp.c_str(), font1, 30);
        labelPlaneHp->setPosition(ccp(30,ScreenHeight-300));
        labelPlaneHp->setColor(ccc3(0, 0, 255));
        this->addChild(labelPlaneHp,10,222);
    }
    //plane0
    if (plane0IsExist) {
        string strPlane0Hp=Convert2String(playerMajor->hp);
        CCLabelTTF* labelPlane0Hp = CCLabelTTF::create(strPlane0Hp.c_str(), font1, 30);
        labelPlane0Hp->setPosition(ccp(30,ScreenHeight-350));
        labelPlane0Hp->setColor(ccc3(0,225, 0));
        this->addChild(labelPlane0Hp,10,333);
    }
    //初始化"分数"文字加入layer中
    CCLabelTTF * label = CCLabelTTF::create("分数:", font1, 20);
    label->setPosition(ccp(30,ScreenHeight-52));
    this->addChild(label,10);
    
    //分数
    std::string strScore=Convert2String(score);
    labelScores = CCLabelTTF::create(strScore.c_str(), font1, 20);
    labelScores->setPosition(ccp(110,ScreenHeight-52));
    labelScores->setColor(ccc3(255, 0, 255));
    this->addChild(labelScores,10);
    
    //杀敌人数
    CCLabelTTF* labelKill = CCLabelTTF::create("杀敌:", font1, 20);
    labelKill->setPosition(ccp(30,ScreenHeight-82));
    this->addChild(labelKill,10);
    
    //杀敌数字加入layer中
    std::string strKillCount=Convert2String(killNum);
    labelKillCount = CCLabelTTF::create(strKillCount.c_str(), font2, 20);
    labelKillCount->setPosition(ccp(110,ScreenHeight-82));
    labelKillCount->setColor(ccc3(255, 0, 255));
    this->addChild(labelKillCount,10);
    
    //距离
    CCLabelTTF* labelDis = CCLabelTTF::create("距离:", font1, 20);
    labelDis->setPosition(ccp(30,ScreenHeight-112));
    this->addChild(labelDis,10);
    
    //距离数字加入layer中
    std::string strDistance=Convert2String(instance);
    labelDistance = CCLabelTTF::create(strDistance.c_str(), font2, 20);
    labelDistance->setPosition(ccp(110,ScreenHeight-112));
    labelDistance->setColor(ccc3(255, 0, 255));
    this->addChild(labelDistance,10);
    
    //钻石
    CCSprite *diamond0 =CCSprite::create("diamond_crystal.png");
    diamond0->setPosition(ccp(30,ScreenHeight-142));
    diamond0->setScale(0.4);
    diamond0->setRotation(30);
    this->addChild(diamond0,200);
    
    CCSprite *diamond1 =CCSprite::create("diamond_yellow.png");
    diamond1->setPosition(ccp(30,ScreenHeight-172));
    diamond1->setScale(0.4);
    diamond1->setRotation(30);
    this->addChild(diamond1,200);
    
    CCSprite *diamond2 =CCSprite::create("diamond_red.png");
    diamond2->setPosition(ccp(30,ScreenHeight-202));
    diamond2->setScale(0.4);
    diamond2->setRotation(30);
    this->addChild(diamond2,200);
    
    
    //钻石数字加入layer中
    string strDiamond=Convert2String(diamond_c);
    labelDiamond = CCLabelTTF::create(strDiamond.c_str(), font2, 20);
    labelDiamond->setPosition(ccp(110,ScreenHeight-142));
    labelDiamond->setColor(ccc3(255, 0, 255));
    this->addChild(labelDiamond,10);
    
    string strDiamond1=Convert2String(diamond_y);
    labelDiamond1 = CCLabelTTF::create(strDiamond1.c_str(), font2, 20);
    labelDiamond1->setPosition(ccp(110,ScreenHeight-172));
    labelDiamond1->setColor(ccc3(255, 0, 255));
    this->addChild(labelDiamond1,10);
    
    string strDiamond2=Convert2String(diamond_r);
    labelDiamond2 = CCLabelTTF::create(strDiamond2.c_str(), font2, 20);
    labelDiamond2->setPosition(ccp(110,ScreenHeight-202));
    labelDiamond2->setColor(ccc3(255, 0, 255));
    this->addChild(labelDiamond2,10);
}

/**
 * 游戏中的操作
 */
void Game::gameOperation()
{
    // 1.添加一个按钮用于结束游戏并返回
    CCMenuItemImage *stopButton=CCMenuItemImage::create("stop.png", "shadow.png", this, menu_selector(Game::goHome));
    stopButton->setPosition(ccp(ScreenWidth/3+50,ScreenHeight/2-100));
    
    // 2.添加一个按钮用于暂停游戏
    CCMenuItemImage *resumeButton=CCMenuItemImage::create("pause.png", "shadow.png", this, menu_selector(Game::pauseGame));
    resumeButton->setPosition(ccp(ScreenWidth/3+50,ScreenHeight/2-200));
    CCMenu* menu =CCMenu::create(stopButton,resumeButton,NULL);
    // 添加操作菜单，z轴最高
    addChild(menu,1);
}

/**
 * 游戏失败
 */
void Game::lostGame()
{
    //存储最高分数
    int oldScore = atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str());
    if(score>oldScore)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Convert2String(score));
        CCUserDefault::sharedUserDefault()->flush();
    }
    //存储最高杀敌数
    int oldKillNum =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_killNum","-1").c_str());
   if(killNum>oldKillNum)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("user_killNum", Convert2String(killNum));
        CCUserDefault::sharedUserDefault()->flush();
    }
    //存储最远距离
    int oldInstance =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_distance","-1").c_str());
   if(instance>oldInstance)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("user_distance", Convert2String(instance));
        CCUserDefault::sharedUserDefault()->flush();
    }
    //存储钻石数据
    int oldDiamond_cry =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_diamond_cry","0").c_str());
        CCUserDefault::sharedUserDefault()->setStringForKey("user_diamond_cry", Convert2String(oldDiamond_cry+diamond_c));
        CCUserDefault::sharedUserDefault()->flush();
    
    int oldDiamond_y =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_diamond_y","0").c_str());
        CCUserDefault::sharedUserDefault()->setStringForKey("user_diamond_y", Convert2String(oldDiamond_y+diamond_y));
        CCUserDefault::sharedUserDefault()->flush();
    
    int oldDiamond_r =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_diamond_r","0").c_str());
        CCUserDefault::sharedUserDefault()->setStringForKey("user_diamond_r", Convert2String(oldDiamond_r+diamond_r));
        CCUserDefault::sharedUserDefault()->flush();

    //添加失败界面
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 190), ScreenWidth, ScreenHeight);
    CCSprite* sp = CCSprite::create("game_lost.png");
    sp->setPosition(ccp(ScreenWidth/2,ScreenHeight/2));
    layer->addChild(sp);
    this->addChild(layer);
    //addChild(layer,255);
    //添加一个按钮用于返回Menu
    CCLabelTTF* ttback =CCLabelTTF::create("返回", font1, 53);
    ttback->setColor(ccc3(0, 255, 255));
    //CCLabelTTF* ttback0 =CCLabelTTF::create("返回", font1, 43);
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback,this, menu_selector(Game::goHome));
    menuLabel->setPosition(ccp(0,-200));
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
    this->addChild(menu);
    //暂停游戏
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();//停背景音乐
    SimpleAudioEngine::sharedEngine()->playEffect("end.mp3");//播放失败音效
    //释放所有的贴图
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCDirector::sharedDirector()->pause();
}

/**
 * 暂停游戏
 */
void Game:: pauseGame()
{
    //按钮音效
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //游戏暂停
    CCDirector::sharedDirector()->pause();
    //暂停背景音乐
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
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
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //移除暂停界面
    this->removeChildByTag(tagCallBack, true);
    //游戏继续
    CCDirector::sharedDirector()->resume();
    //继续背景音乐
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

/**
 * 返回主菜单
 */
void Game::goHome()
{
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);

    //this->removeAllComponents();
    //停止所有计时器
    this->unscheduleAllSelectors();
    //停止所有音效
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    //继续游戏
    CCDirector::sharedDirector()->resume();
    //切换到"菜单"场景
    CCDirector::sharedDirector()->replaceScene(Menu::scene());
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menu_bg_music.mp3",true);

}

/**
 * 计算两点之间的距离
 */
float Game::Distance(CCPoint point1,CCPoint point2)
{
    return sqrt(pow((point1.x-point2.x),2)+pow(point1.y-point2.y, 2));
}

/**
 * 注册多触点的委托监听
 */
void Game::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

/**
 * 用户手指进行移动或者拖拽
 */
void Game::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    if(plane0IsExist)
    {
    for (; iter !=pTouches->end(); iter++)
    {
        //获取两个飞机对象
        CCPoint point1=playerMajor->getPosition();
        CCPoint point2=playerAuxiliary->getPosition();
        CCTouch *pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        //根据触点与两个飞机之间的距离判断触控情况
        //首先触点与飞机必须足够近，不然用户并没有触碰到飞机
        //触点应该给相对较近的那个飞机
        if (pTouch->getID()==0)
        {
            if (Distance(location, point1)<Distance(location, point2)&&Distance(location, point1)<100.0) {
                playerMajor->setPosition(location);
            }
            else if(Distance(location, point2)<100.0)
                playerAuxiliary->setPosition(location);
        }
        else if (pTouch->getID()==1)
        {
            if (Distance(location, point2)<Distance(location, point1)&&Distance(location, point2)<100.0) {
                playerAuxiliary->setPosition(location);
            }
            else if(Distance(location, point1)<100.0)
                playerMajor->setPosition(location);
        }
    }
    }else{
        CCPoint point1=playerMajor->getPosition();
        CCTouch *pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        if (Distance(point1, location)<=playerMajor->getContentSize().width){
            playerMajor->setPosition(location);
        }
    }
}

/**
 * 删除多触点的委托监听
 */
void Game::onExit()
{
    this->unscheduleUpdate();
    this->unscheduleAllSelectors();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

/**
 * 析构函数
 */
Game::~Game(){
    CC_SAFE_RELEASE(arrayEnemy);
}
