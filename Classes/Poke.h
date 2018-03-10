#ifndef __POKE_H__
#define __POKE_H__

#include "cocos2d.h"

enum PokeNum // 牌值
{
	NUM_3 = 0,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_10,
	NUM_J,
	NUM_Q,
	NUM_K,
	NUM_A,
	NUM_2,
	NUM_XW,
	NUM_DW
};

enum PokeTag // 花色
{
	FANGKUAI = 0,
	MEIHUA,
	HONGTAO ,
	HEITAO
};

struct PokeInfo
{
	PokeNum _num;
	PokeTag _tag;

	inline bool operator==(const PokeInfo &pi) const
	{
		return (this->_num==pi._num && this->_tag==pi._tag);
	}
};

class SceneGame;

class Poke : public cocos2d::Sprite
{
public:

	static Poke* create(PokeInfo info, bool isSmall = false);

	virtual bool init(PokeInfo info, bool isSmall = false);

	void SetTouchEnabled();

	bool isSelected() { return _isSelected; };
	void click();
	// 取消选中
	void unSelect();
	void Select();

	PokeInfo getInfo() { return _info; };

	cocos2d::Rect getRect();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	CC_SYNTHESIZE(SceneGame*,_gameMain,GameMain);

	PokeInfo	_info;

protected:

	bool		_isSelected;

	cocos2d::Size _size;
};

#endif // __POKE_H__
