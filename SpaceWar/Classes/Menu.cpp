//
//  Menu.cpp
//  星际联盟
//
//  Created by 919575700@qq.com on 3/31/14.
//
//
#include "Menu.h"
#include "Map.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
/**
 * 枚举tag
 */
enum tag_menu{
    tagRightPlane,     //右边飞机的tag
    tagSwitchControl,  //模式切换按钮组件
    tagColorLayer,     //颜色遮罩层
};

/**
 * 构造函数
 * 实例化一个菜单页面
 */
CCScene* Menu::scene()
{
    //创建一个场景作为菜单界面
    CCScene *scene = CCScene::create();
    //菜单层
    Menu *layer = Menu::create();
    //菜单添加到场景界面
    scene->addChild(layer);
    return scene;
}

/**
 * 初始化菜单
 */
bool Menu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    // 打印屏幕尺寸
    //cout<<"screenWidth:"<<ScreenWidth<<endl;
    //cout<<"screenHeight:"<<ScreenHeight<<endl;
    addUI();
    this->scheduleUpdate();
    return true;
}

void Menu::onEnter() {
    CCLayer::onEnter();
}

void Menu::addUI() {
    // 1.开场背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menu_bg_music.mp3",true);
    
    // 2.开场背景,主界面
    //创建精灵贴图当菜单背景
    CCSprite* menuBg = CCSprite::create("menu_bg.png");
    menuBg->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    //添加背景子视图
    addChild(menuBg);
    
    // 3.左边飞机动画
    //左边飞机精灵贴图
    CCSprite* planeLeft = CCSprite::create("menu_plane_left0.png");
    //左边飞机的位置
    planeLeft->setPosition(ccp(100,100));
    //左边飞机动画
    CCAnimation *animationLeft = CCAnimation::create();
    // 添加帧
    for (int i = 1; i <= 5; i++) {
        CCString *filename = CCString::create("");
        filename->initWithFormat("menu_plane_left%d.png", i);
        animationLeft->addSpriteFrameWithFileName(filename->getCString());
    }
    //每张帧图停留的时间
    animationLeft->setDelayPerUnit(0.03f);
    //设置无限循环播放
    animationLeft->setLoops(-1);
    //重新加载起始帧
    animationLeft->setRestoreOriginalFrame(false);
    //创建左边动画
    CCAnimate *animateLeft = CCAnimate::create(animationLeft);
    //左边飞机运行动画
    planeLeft->runAction(animateLeft);
    //左边飞机加入菜单界面
    addChild(planeLeft);
    
    // 4.右边飞机动画
    //右边飞机贴图
    CCSprite* planeRight = CCSprite::create("menu_plane_right.png");
    planeRight->setTag(tagRightPlane);
    //右边飞机位置
    planeRight->setPosition(ccp(ScreenWidth-100, 100));
    //右边飞机加入菜单页面，并为它打上tag
    addChild(planeRight);
    
    // 5.添加离子动画
    CCParticleSystemQuad * particleLight = CCParticleSystemQuad::create("particle_color.plist");
    //离子源位置
    particleLight->setPosition(ScreenWidth/2,ScreenHeight/3);
    //添加离子源
    //addChild(particleLight);
    
    // 6.游戏模式选择按钮
    //按钮文字
    CCLabelTTF *singleTTF = CCLabelTTF::create("双机模式", font1, 30);
    CCLabelTTF *doubleTTF = CCLabelTTF::create("单机模式", font1, 30);
    //选择按钮组件
    CCControlSwitch *modelSwitch = CCControlSwitch::create(
                                                           CCSprite::create("menu_switch_bg.png"),
                                                           CCSprite::create("menu_switch_bg.png"),
                                                           CCSprite::create("menu_switch_bg.png"),
                                                           CCSprite::create("menu_switch_dot.png"),
                                                           singleTTF,
                                                           doubleTTF);
    //按钮组件位置
    modelSwitch->setPosition(ccp(ScreenWidth/2,100));
    //设置起始状态为开
    modelSwitch->setOn(true);
    //允许交互
    modelSwitch->setEnabled(true);
    //设置tag
    modelSwitch->setTag(tagSwitchControl);
    //添加按钮组件到菜单界面
    addChild(modelSwitch);
    
    // 7.菜单按钮
    //开始游戏按钮
    CCMenuItemImage *itemPlay= CCMenuItemImage::create("menu_button0.png", "menu_button_bg.png",this,menu_selector(Menu::playIsPressed));
    itemPlay->setPosition(ccp(0,-200));
    //战绩按钮
    CCMenuItemImage *itemScore= CCMenuItemImage::create("menu_button1.png", "menu_button_bg.png",this,menu_selector(Menu::scoreIsPressed));
    itemScore->setPosition(ccp(0,100));
    //关于我们按钮
    CCMenuItemImage *itemAbout= CCMenuItemImage::create("menu_button2.png", "menu_button_bg.png",this,menu_selector(Menu::aboutIsPressed));
    itemAbout->setPosition(ccp(0,0));
    //设置按钮
    CCMenuItemImage *itemSet= CCMenuItemImage::create("menu_button3.png", "menu_button_bg.png",this,menu_selector(Menu::setIsPressed));
    itemSet->setPosition(ccp(0,-100));
    //创建Menu菜单，加入各按钮
    CCMenu *menu = CCMenu::create(itemPlay,itemScore,itemAbout,itemSet,NULL);
    //菜单组位置
    menu->setPosition(ScreenWidth/2,ScreenHeight/2);
    //添加菜单到界面
    addChild(menu);
}

/**
 * 控制右边飞机的显示与隐藏
 */
void Menu::update(float time)
{
    // 获取右边的飞机贴图
    CCSprite *planeRight=(CCSprite*)getChildByTag(tagRightPlane);
    // 每一帧切换右边飞机显示、隐藏状态
    if (show == true) {
        planeRight->setVisible(false);
        show = false;
    }
    else
    {
        planeRight->setVisible(true);
        show = true;
    }
}

/**
 * 按下开始游戏按钮
 */
void Menu::playIsPressed(){
    //播放点击按钮音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //获取模式切换按钮组件
    CCControlSwitch *modelSwitch = (CCControlSwitch*)getChildByTag(tagSwitchControl);
    //判断模式切换按钮组件状态设置不同游戏模式
    if (modelSwitch->isOn()) {
        //如果是双机模式
        CCUserDefault::sharedUserDefault()->setBoolForKey("choosedModel", true);
    }else{
        //单机模式
        CCUserDefault::sharedUserDefault()->setBoolForKey("choosedModel", false);
    }
    //切换到游戏场景
    CCDirector::sharedDirector()->replaceScene(transition::create(turnTime, Game::scene()));
}

/**
 * 按下战绩按钮
 */
void Menu::scoreIsPressed(){
    // 0.播放点击按钮音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    
    // 1.颜色层
    CCLayerColor *grayLayer = CCLayerColor::create(ccc4(0, 0, 0, 180), ScreenWidth, ScreenHeight);
    //标记
    grayLayer->setTag(tagColorLayer);
    addChild(grayLayer);
    // 1.对话框
    CCSprite *sprtDialog = CCSprite::create("menu_pop_bg.png");
    sprtDialog->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    grayLayer->addChild(sprtDialog);
    // 2.关闭按钮
    CCMenuItemImage *closeButton=CCMenuItemImage::create("menu_close_button.png","menu_shadow.png",this,menu_selector(Menu::closeUs));
    closeButton->setPosition(ccp(sprtDialog->getContentSize().width-closeButton->getContentSize().width, sprtDialog->getContentSize().height-closeButton->getContentSize().height));
    CCMenu *us_menu = CCMenu::create(closeButton,NULL);
    us_menu->setPosition(ccp(0, 0));
    sprtDialog->addChild(us_menu);
    
    // 3.最高分、最高杀敌数、最远距离
    //标签字符串
    CCLabelTTF *ttfShow = CCLabelTTF::create("最高分数：",font1,30);
    ttfShow->setPosition(ccp(ScreenWidth/2-100,300));
    ttfShow->setColor(ccc3(255,255,255));
    sprtDialog->addChild(ttfShow);
    CCLabelTTF *ttfShow1 = CCLabelTTF::create("最高杀敌：",font1, 30);
    ttfShow1->setPosition(ccp(ScreenWidth/2-100,200));
    ttfShow1->setColor(ccc3(255, 255, 255));
    sprtDialog->addChild(ttfShow1);
    CCLabelTTF *ttfShow2 = CCLabelTTF::create("最远距离：", font1, 30);
    ttfShow2->setPosition(ccp(ScreenWidth/2-100,100));
    ttfShow2->setColor(ccc3(255, 255, 255));
    sprtDialog->addChild(ttfShow2);
    //获取数据
    std::string score =CCUserDefault::sharedUserDefault()->getStringForKey("user_score","0");
    std::string skillNum =CCUserDefault::sharedUserDefault()->getStringForKey("user_killNum","0");
    std::string instance =CCUserDefault::sharedUserDefault()->getStringForKey("user_distance","0");
    //数据字符串
    CCLabelTTF* ttfScore = CCLabelTTF::create(score.c_str(), font2, 30);
    CCLabelTTF* ttfSkillNum = CCLabelTTF::create(skillNum.c_str(),font2, 30);
    CCLabelTTF* ttfDistance = CCLabelTTF::create(instance.c_str(), font2, 30);
    //数据字符位置
    ttfScore->setPosition(ccp(ScreenWidth/2+50,300));
    ttfSkillNum->setPosition(ccp(ScreenWidth/2+50,200));
    ttfDistance->setPosition(ccp(ScreenWidth/2+50,100));
    //数据字符颜色
    ttfScore->setColor(ccc3(255, 0, 225));
    ttfSkillNum->setColor(ccc3(255, 0, 225));
    ttfDistance->setColor(ccc3(255,0,225));
    //数据字符添加到界面
    sprtDialog->addChild(ttfScore);
    sprtDialog->addChild(ttfSkillNum);
    sprtDialog->addChild(ttfDistance);
}

/*
 * 按下关于我们
 */
void Menu::aboutIsPressed(){
    //播放点击按钮音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    
    // 0.颜色层
    CCLayerColor *grayLayer = CCLayerColor::create(ccc4(0, 0, 0, 180), ScreenWidth, ScreenHeight);
    //标记
    grayLayer->setTag(tagColorLayer);
    addChild(grayLayer);
    // 1.对话框
    CCSprite *sprtDialog = CCSprite::create("menu_pop_bg.png");
    sprtDialog->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    grayLayer->addChild(sprtDialog);
    // 2.关闭按钮
    CCMenuItemImage *closeButton=CCMenuItemImage::create("menu_close_button.png","menu_shadow.png",this,menu_selector(Menu::closeUs));
    closeButton->setPosition(ccp(sprtDialog->getContentSize().width-closeButton->getContentSize().width, sprtDialog->getContentSize().height-closeButton->getContentSize().height));
    CCMenu *us_menu = CCMenu::create(closeButton,NULL);
    us_menu->setPosition(ccp(0, 0));
    sprtDialog->addChild(us_menu);
    // 3.开发者信息
    CCLabelTTF *about=CCLabelTTF::create("开发者(Developer)：\n蒋信厚(JiangXinhou)",font2,40);
    about->setPosition(ccp(sprtDialog->getContentSize().width/2,sprtDialog->getContentSize().height/2));
    sprtDialog->addChild(about);
}

/*
 * 按下设置
 */
void Menu::setIsPressed(){
    //播放点击按钮音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    // 0.颜色层
    CCLayerColor *grayLayer = CCLayerColor::create(ccc4(0, 0, 0, 180), ScreenWidth, ScreenHeight);
    //标记
    grayLayer->setTag(tagColorLayer);
    addChild(grayLayer);
    // 1.对话框
    CCSprite *sprtDialog = CCSprite::create("menu_pop_bg.png");
    sprtDialog->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    grayLayer->addChild(sprtDialog);
    // 2.关闭按钮
    CCMenuItemImage *closeButton=CCMenuItemImage::create("menu_close_button.png","menu_shadow.png",this,menu_selector(Menu::closeUs));
    closeButton->setPosition(ccp(sprtDialog->getContentSize().width-closeButton->getContentSize().width, sprtDialog->getContentSize().height-closeButton->getContentSize().height));
    // 2.音乐开关
    CCMenuItemImage *music_off = CCMenuItemImage::create("menu_music_on.png", "menu_shadow.png",this,menu_selector(Menu::musicOff));
    CCMenuItemImage *music_on = CCMenuItemImage::create("menu_music_off.png", "menu_shadow.png",this,menu_selector(
        Menu::musicOn));
    music_on->setPosition(ccp(sprtDialog->getContentSize().width/2-50,sprtDialog->getContentSize().height/2));
    music_off->setPosition(ccp(sprtDialog->getContentSize().width/2+50,sprtDialog->getContentSize().height/2));
    
    CCMenu *set_menu = CCMenu::create(closeButton,music_on,music_off,NULL);
    set_menu->setPosition(ccp(0, 0));
    sprtDialog->addChild(set_menu);
}

/**
 * 关闭关于我们
 */
void Menu::closeUs() {
    //播放点击按钮音效
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    this->removeChildByTag(tagColorLayer);
}

/**
 *音乐开关
 */
void Menu::musicOn() {
    //暂停播放背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
void Menu::musicOff() {
    //继续播放背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void Menu::onExit() {
    CCLayer::onExit();
}

Menu::~Menu() {
}
