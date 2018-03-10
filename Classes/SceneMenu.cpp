#include "SceneMenu.h"
#include "SceneGame.h"
#include"SimpleAudioEngine.h"   //������������ͷ�ļ�  
#include "AppMacros.h"

USING_NS_CC;  
using namespace CocosDenshion;//ʹ�ø���������������ռ�  

Scene* SceneMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = SceneMenu::create();
    scene->addChild(layer);

    return scene;
}

bool SceneMenu::init()
{
    // ��ʼ������----------------------------------------
    if ( !Layer::init() )
    {
        return false;
    }

	// ���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/table_background_music.mp3", true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����----------------------------------------------
	auto bg = Sprite::create("beijing.png");
	//bg->setScale(1/0.8);
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	auto logo = Sprite::create("game_logo.png");
	logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3 * 2 + origin.y));
	this->addChild(logo, 0);

	// �����˵�---------------------------------------------

	auto itemBegin = customMenuItem("item_begin.png", "item_begin.png", CC_CALLBACK_1(SceneMenu::menuBeginCallback, this));
	itemBegin->setPosition(Vec2(-200/SCALE_FACTOR,-200/SCALE_FACTOR));
	auto itemExit = customMenuItem("item_exit.png", "item_exit.png", CC_CALLBACK_1(SceneMenu::menuExitCallback, this));
	itemExit->setPosition(Vec2(200/SCALE_FACTOR,-200/SCALE_FACTOR));

    auto menu = Menu::create(itemBegin, itemExit, NULL);
    this->addChild(menu, 1);
    
    return true;
}


void SceneMenu::menuBeginCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(SceneGame::createScene());
}

void SceneMenu::menuExitCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->end();
}