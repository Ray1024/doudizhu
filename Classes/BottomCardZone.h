#ifndef __BOTTOM_CARD_ZONE_H__
#define __BOTTOM_CARD_ZONE_H__

#include "cocos2d.h"
#include "Poke.h"

//---------------------------------------------
// µ×ÅÆÏÔÊ¾Çø
//---------------------------------------------
class BottomCardZone : public cocos2d::Sprite
{

public:

	static BottomCardZone* create();

    virtual bool init();

	void Show(PokeInfo cardInfo);
};

#endif // __BOTTOM_CARD_ZONE_H__
