//
//  Plane0.h
//  星际联盟
//
//  Created by 919575700@qq.com on 4/2/14.
//
//
#include "Prefix.h"
/**
 * 枚举两张地图背景的交替出现
 */
typedef enum{
    tag_oneImg0,
    tag_twoImg0,
}tagMap;

class HMap : public cocos2d::CCLayer
{
public:
    /**
     * 地图静态单例
     */
    static HMap* createMap(const char* fileName);
private:
    /**
     * 初始化
     */
    void mapInit(const char* fileName);
    /**
     * 系统按帧更新检测
     */
    void update(float time);
    /**
     * 生命周期函数的退出
     */
    virtual void onExit();
};