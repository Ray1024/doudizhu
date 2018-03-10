/**********************************************************************
@file		AppMacros.h
@brief		��Ϸ�ĺ궨���ļ�
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

//��ͬƽ̨�ĳߴ綨��----------------------------------------

#define ANDROID_MI3		// ��ֲ��С��3ƽ̨

#ifdef ANDROID_MI3

// ���ű���
#define		SCALE_FACTOR	0.625f
#define		WINSIZE_W		1920
#define		WINSIZE_H		1080

#else

// ���ű���
#define		SCALE_FACTOR		1.f
#define		WINSIZE_W			1200
#define		WINSIZE_H			675

#endif // ANDROID_MI3
//----------------------------------------------------------


#endif /* __APPMACROS_H__ */
