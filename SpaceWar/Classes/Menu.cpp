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
/**
 * 枚举tag
 */
enum tag{
    tagRightPlane,//右边飞机的tag
    tagSwitchControl,//模式切换按钮组件
    tagColorLayer,//颜色遮罩层
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
    // 0.初始化右边飞机显示状态
    show = true;
    
    // 1.开场背景音乐
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menu_bg_music.mp3",true);
    
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
    animationLeft->addSpriteFrameWithFileName("menu_plane_left1.png");
    animationLeft->addSpriteFrameWithFileName("menu_plane_left2.png");
    animationLeft->addSpriteFrameWithFileName("menu_plane_left3.png");
    animationLeft->addSpriteFrameWithFileName("menu_plane_left4.png");
    animationLeft->addSpriteFrameWithFileName("menu_plane_left5.png");
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
    //右边飞机位置
    planeRight->setPosition(ccp(ScreenWidth-100, 100));
    //右边飞机加入菜单页面，并为它打上tag
    addChild(planeRight, 1, tagRightPlane);
    
    // 5.添加离子动画
    CCParticleSystemQuad * particleLight = CCParticleSystemQuad::create("particle_color.plist");
    //离子源位置
    particleLight->setPosition(ScreenWidth/2,ScreenHeight/3);
    //添加离子源
    addChild(particleLight);
    
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
    
    // 5.菜单按钮
    //开始游戏按钮
    CCMenuItemImage * itemPlay= CCMenuItemImage::create("menu_button0.png", "menu_button_bg.png",this,menu_selector(Menu::playIsPressed));
    itemPlay->setPosition(ccp(0,-200));
    //战绩按钮
    CCMenuItemImage * itemScore= CCMenuItemImage::create("menu_button1.png", "menu_button_bg.png",this,menu_selector(Menu::scoreIsPressed));
    itemScore->setPosition(ccp(0,100));
    //关于我们按钮
    CCMenuItemImage * itemAbout= CCMenuItemImage::create("menu_button2.png", "menu_button_bg.png",this,menu_selector(Menu::aboutIsPressed));
    itemAbout->setPosition(ccp(0,0));
    //设置按钮
    CCMenuItemImage * itemSet= CCMenuItemImage::create("menu_button3.png", "menu_button_bg.png",this,menu_selector(Menu::setIsPressed));
    itemSet->setPosition(ccp(0,-100));
    //创建Menu菜单，加入各按钮
    CCMenu * menu = CCMenu::create(itemPlay,itemScore,itemAbout,itemSet,NULL);
    //菜单组位置
    menu->setPosition(ScreenWidth/2,ScreenHeight/2);
    //添加菜单到界面
    addChild(menu);
    
    // 6.界面系统刷新
    this->scheduleUpdate();
    return true;
}
/**
 * 控制右边飞机的显示与隐藏
 */
void Menu::update(float time)
{
    //获取右边的飞机贴图
    CCSprite *planeRight=(CCSprite*)getChildByTag(tagRightPlane);
    //每一帧切换右边飞机显示、隐藏状态
    if (show==true) {
        planeRight->setVisible(false);
        show=false;
    }
    else
    {
        planeRight->setVisible(true);
        show=true;
    }
}
/**
 * 按下开始游戏按钮
 */
void Menu::playIsPressed(){
    //播放点击按钮音效
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
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
 *按下战绩按钮
 */
void Menu::scoreIsPressed(){
    // 1.播放点击按钮音效
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    
    // 2.颜色遮罩层
    CCLayerColor *aboutLayer = CCLayerColor::create(ccc4(0, 0, 0, 180), ScreenWidth, ScreenHeight);
    //标记颜色层
    aboutLayer->setTag(tagColorLayer);
    //关闭按钮
    CCMenuItemImage *_return = CCMenuItemImage::create("menu_close_purple.png","menu_shadow.png",this,menu_selector(Menu::closeUs));
    //按钮位置
    _return->setPosition(ccp(220, 120));
    //创建承载按钮的菜单
    CCMenu *us_menu = CCMenu::create(_return,NULL);
    //菜单的位置
    us_menu->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    //对话框背景贴图
    CCSprite *sprtDialog = CCSprite::create("menu_ranking.png");
    //对话框背景位置
    sprtDialog->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    //皇冠图片
    CCSprite *crown=CCSprite::create("menu_crown.png");
    //皇冠图片位置
    crown->setPosition(ccp(ScreenWidth/2, ScreenHeight/1.3));
    //添加各图片组件到遮罩层
    aboutLayer->addChild(crown);
    aboutLayer->addChild(sprtDialog);
    aboutLayer->addChild(us_menu);
    //遮罩层添加到界面
    addChild(aboutLayer);
    // 3.最高分、最高杀敌数、最远距离
    //标签字符串
    CCLabelTTF *ttfShow = CCLabelTTF::create("最高分数：",font1,30);
    ttfShow->setPosition(ccp(ScreenWidth/2-100,ScreenHeight/2+100));
    ttfShow->setColor(ccc3(255,255,255));
    aboutLayer->addChild(ttfShow);
    CCLabelTTF *ttfShow1 = CCLabelTTF::create("最高杀敌：",font1, 30);
    ttfShow1->setPosition(ccp(ScreenWidth/2-100,ScreenHeight/2+50));
    ttfShow1->setColor(ccc3(255, 255, 255));
    aboutLayer->addChild(ttfShow1);
    CCLabelTTF *ttfShow2 = CCLabelTTF::create("最远距离：", font1, 30);
    ttfShow2->setPosition(ccp(ScreenWidth/2-100,ScreenHeight/2));
    ttfShow2->setColor(ccc3(255, 255, 255));
    aboutLayer->addChild(ttfShow2);
    //获取数据
    std::string score =CCUserDefault::sharedUserDefault()->getStringForKey("user_score","0");
    std::string skillNum =CCUserDefault::sharedUserDefault()->getStringForKey("user_killNum","0");
    std::string instance =CCUserDefault::sharedUserDefault()->getStringForKey("user_distance","0");
    //数据字符串
    CCLabelTTF* ttfScore = CCLabelTTF::create(score.c_str(), font2, 30);
    CCLabelTTF* ttfSkillNum = CCLabelTTF::create(skillNum.c_str(),font2, 30);
    CCLabelTTF* ttfDistance = CCLabelTTF::create(instance.c_str(), font2, 30);
    //数据字符位置
    ttfScore->setPosition(ccp(ScreenWidth/2+50,ScreenHeight/2+100));
    ttfSkillNum->setPosition(ccp(ScreenWidth/2+50,ScreenHeight/2+50));
    ttfDistance->setPosition(ccp(ScreenWidth/2+50,ScreenHeight/2));
    //数据字符颜色
    ttfScore->setColor(ccc3(255, 0, 225));
    ttfSkillNum->setColor(ccc3(255, 0, 225));
    ttfDistance->setColor(ccc3(255,0,225));
    //数据字符添加到界面
    aboutLayer->addChild(ttfScore);
    aboutLayer->addChild(ttfSkillNum);
    aboutLayer->addChild(ttfDistance);
}
//按下关于我们
void Menu::aboutIsPressed(){
    //播放点击按钮音效
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //颜色层
    CCLayerColor *aboutLayer = CCLayerColor::create(ccc4(0, 0, 0, 180), ScreenWidth, ScreenHeight);
    //标记颜色层
    aboutLayer->setTag(tagColorLayer);
    //关闭按钮
    CCMenuItemImage *_return=CCMenuItemImage::create("menu_close_blue.png","menu_shadow.png",this,menu_selector(Menu::closeUs));
    _return->setPosition(ccp(170, 190));
    CCMenu *us_menu = CCMenu::create(_return,NULL);
    us_menu->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    //对话框
    CCSprite *sprtDialog = CCSprite::create("menu_dialog_about.png");
    sprtDialog->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    //开发者信息
    CCLabelTTF *about=CCLabelTTF::create("开发者：\n蒋信厚",font2,40);
    about->setColor(ccc3(102, 0, 153));
    about->setPosition(ccp(sprtDialog->getContentSize().width/2,sprtDialog->getContentSize().height/2));
    sprtDialog->addChild(about);
    aboutLayer->addChild(sprtDialog);
    aboutLayer->addChild(us_menu);
    addChild(aboutLayer);
}
//按下设置
void Menu::setIsPressed(){
    //播放点击按钮音效
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    //颜色层
    CCLayerColor *aboutLayer = CCLayerColor::create(ccc4(0, 0, 0, 180), ScreenWidth, ScreenHeight);
    //标记颜色层
    aboutLayer->setTag(tagColorLayer);
    //关闭按钮
    CCMenuItemImage *_return = CCMenuItemImage::create("menu_close_blue.png","menu_shadow.png",this,menu_selector(Menu::closeUs));
    _return->setPosition(ccp(-125, 155));
    //音乐开关
    CCMenuItemImage *music_off = CCMenuItemImage::create("menu_music_on.png", "menu_shadow.png",this,menu_selector(Menu::musicOff));
    CCMenuItemImage *music_on = CCMenuItemImage::create("menu_music_off.png", "menu_shadow.png",this,menu_selector(
        Menu::musicOn));
    music_on->setPosition(ccp(-50,0));
    music_off->setPosition(ccp(50,0));
    CCMenu *us_menu = CCMenu::create(_return,music_on,music_off,NULL);
    us_menu->setPosition(ccp(ScreenWidth/2,ScreenHeight/2));
    //对话框
    CCSprite *sprtDialog = CCSprite::create("menu_set_bg.png");
    sprtDialog->setPosition(ccp(ScreenWidth/2, ScreenHeight/2));
    //将音量滑动条放到对话框上
    aboutLayer->addChild(sprtDialog);
    aboutLayer->addChild(us_menu);
    addChild(aboutLayer);
}
/**
 *关闭关于我们
 */
void Menu::closeUs(){
    //播放点击按钮音效
    SimpleAudioEngine::sharedEngine()->playEffect(clickEffect);
    this->removeChildByTag(tagColorLayer);
}
/**
 *音乐开关
 */
void Menu::musicOn(){
    //暂停播放背景音乐
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
void Menu::musicOff(){
    //继续播放背景音乐
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}