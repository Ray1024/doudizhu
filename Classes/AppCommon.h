/**********************************************************************
@file		AppCommon.h
@brief		游戏的宏定义文件
@author		Ray1024
@date		2016-12-21
***********************************************************************/

#ifndef __APPCOMMON_H__
#define __APPCOMMON_H__

#include "cocos2d.h"
#include "Player.h"

// 创建自定义菜单项
cocos2d::MenuItemSprite* customMenuItem(const std::string& normalImage, const std::string& disabledImage, const cocos2d::ccMenuCallback& callback);
cocos2d::MenuItemSprite* customMenuItemWithSpriteFrameName(const std::string& normalImage, const std::string& disabledImage, const cocos2d::ccMenuCallback& callback);

// 判断是否连续
bool IsContinuous(cocos2d::CCArray* vecPoke);
bool IsContinuous(std::vector<int>& vec);

// 判断是否都小于2
bool IsLessTwo(cocos2d::CCArray* vecPoke);
bool IsLessTwo(std::vector<int>& vecPoke);

CARDS_DATA PanDuanPaiXing(cocos2d::CCArray* cards);//判断牌型
CARDS_DATA PanDuanPaiXing(std::vector<PokeInfo>& cards);//判断牌型
CARDS_DATA PanDuanPaiXing(std::vector<int>& cards);//判断牌型

#endif //__APPCOMMON_H__