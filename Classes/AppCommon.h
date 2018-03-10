/**********************************************************************
@file		AppCommon.h
@brief		��Ϸ�ĺ궨���ļ�
@author		Ray1024
@date		2016-12-21
***********************************************************************/

#ifndef __APPCOMMON_H__
#define __APPCOMMON_H__

#include "cocos2d.h"
#include "Player.h"

// �����Զ���˵���
cocos2d::MenuItemSprite* customMenuItem(const std::string& normalImage, const std::string& disabledImage, const cocos2d::ccMenuCallback& callback);
cocos2d::MenuItemSprite* customMenuItemWithSpriteFrameName(const std::string& normalImage, const std::string& disabledImage, const cocos2d::ccMenuCallback& callback);

// �ж��Ƿ�����
bool IsContinuous(cocos2d::CCArray* vecPoke);
bool IsContinuous(std::vector<int>& vec);

// �ж��Ƿ�С��2
bool IsLessTwo(cocos2d::CCArray* vecPoke);
bool IsLessTwo(std::vector<int>& vecPoke);

CARDS_DATA PanDuanPaiXing(cocos2d::CCArray* cards);//�ж�����
CARDS_DATA PanDuanPaiXing(std::vector<PokeInfo>& cards);//�ж�����
CARDS_DATA PanDuanPaiXing(std::vector<int>& cards);//�ж�����

#endif //__APPCOMMON_H__