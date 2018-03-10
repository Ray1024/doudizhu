#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "cocos2d.h"
#include "AppCommon.h"

//---------------------------------------------
// 菜单场景
//---------------------------------------------
class SceneMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // 菜单回调
    void menuBeginCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(SceneMenu);
};

#endif // __SCENE_MENU_H__
