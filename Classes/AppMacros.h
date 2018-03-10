/**********************************************************************
@file		AppMacros.h
@brief		游戏的宏定义文件
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

//不同平台的尺寸定义----------------------------------------

#define ANDROID_MI3		// 移植到小米3平台

#ifdef ANDROID_MI3

// 缩放比例
#define		SCALE_FACTOR	0.625f
#define		WINSIZE_W		1920
#define		WINSIZE_H		1080

#else

// 缩放比例
#define		SCALE_FACTOR		1.f
#define		WINSIZE_W			1200
#define		WINSIZE_H			675

#endif // ANDROID_MI3
//----------------------------------------------------------


#endif /* __APPMACROS_H__ */
