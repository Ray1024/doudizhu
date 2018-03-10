#include "Poke.h"
#include "SceneGame.h"
#include "AppMacros.h"

USING_NS_CC;

Poke* Poke::create(PokeInfo info, bool isSmall)
{
	Poke *sprite = new (std::nothrow) Poke();
	if (sprite && sprite->init(info, isSmall))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

char* poke_text[] = {
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"J",
	"Q",
	"K",
	"A",
	"2",
	"w",
	"W",
};

bool Poke::init(PokeInfo info, bool isSmall)
{
	// 初始化基类--------------------------------------------------------------
	if ( !Sprite::init() )
	{
		return false;
	}

	_info = info;

	if (isSmall)
	{
		auto cardFront = Label::createWithSystemFont(poke_text[_info._num], "arial", 24);
		this->addChild(cardFront);
		_size = cardFront->getContentSize();
	}
	else
	{
		auto cardFront = Sprite::createWithSpriteFrameName("b/bg.png");
		this->addChild(cardFront);
		_size = cardFront->getContentSize();

		if (_info._num == PokeNum::NUM_XW)
		{
			auto cardNum = Sprite::createWithSpriteFrameName("b/smalltag_4.png");
			cardNum->setPosition(-50/SCALE_FACTOR,10/SCALE_FACTOR);
			this->addChild(cardNum);

			auto cardTag = Sprite::createWithSpriteFrameName("b/bigtag_6.png");
			cardTag->setPosition(20/SCALE_FACTOR,-30/SCALE_FACTOR);
			this->addChild(cardTag);
		} 
		else if (_info._num == PokeNum::NUM_DW)
		{
			auto cardNum = Sprite::createWithSpriteFrameName("b/smalltag_5.png");
			cardNum->setPosition(-50/SCALE_FACTOR,10/SCALE_FACTOR);
			this->addChild(cardNum);

			auto cardTag = Sprite::createWithSpriteFrameName("b/bigtag_6.png");
			cardTag->setPosition(20/SCALE_FACTOR,-30/SCALE_FACTOR);
			this->addChild(cardTag);
		}
		else 
		{
			unsigned int num = 0;

			if (_info._num == NUM_A)
			{
				num = 0;
			}
			else if (_info._num == NUM_2)
			{
				num = 1;
			}
			else
			{
				num = _info._num + 2;
			}

			std::stringstream strTag;
			strTag << "b/bigtag_" << _info._tag << ".png";
			auto cardSmallTag = Sprite::createWithSpriteFrameName(strTag.str());
			cardSmallTag->setScale(0.5);
			cardSmallTag->setPosition(-50/SCALE_FACTOR,20/SCALE_FACTOR);
			this->addChild(cardSmallTag);

			if (_info._tag == HEITAO || _info._tag == MEIHUA)
			{
				std::stringstream strNum;
				strNum << "b/black_" << num << ".png";
				auto cardNum = Sprite::createWithSpriteFrameName(strNum.str());
				cardNum->setPosition(-50/SCALE_FACTOR,70/SCALE_FACTOR);
				this->addChild(cardNum);
			}
			else
			{
				std::stringstream strNum;
				strNum << "b/red_" << num << ".png";
				auto cardNum = Sprite::createWithSpriteFrameName(strNum.str());
				cardNum->setPosition(-50/SCALE_FACTOR,70/SCALE_FACTOR);
				this->addChild(cardNum);
			}

			auto cardTag = Sprite::createWithSpriteFrameName(strTag.str());
			cardTag->setPosition(20/SCALE_FACTOR,-30/SCALE_FACTOR);
			this->addChild(cardTag);
		}
	}

	_isSelected = false;

	return true;
}

void Poke::SetTouchEnabled()
{
	// 触摸事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(Poke::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Poke::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Poke::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Poke::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

Rect Poke::getRect()
{
	return Rect(-_size.width / 2, -_size.height / 2, _size.width, _size.height);
}

bool Poke::onTouchBegan(Touch* touch, Event* event)
{
	if (getRect().containsPoint(convertTouchToNodeSpaceAR(touch)))
	{
		click();

		return true;
	}

	return false;
}

void Poke::onTouchEnded(Touch* touch, Event* event)
{

}

void Poke::onTouchCancelled(Touch* touch, Event* event)
{

}

void Poke::onTouchMoved(Touch* touch, Event* event)
{

}

void Poke::click()
{
	CCArray* arr = _gameMain->getArrPlayerOut();

	if (_isSelected)
	{
		setPosition(_position.x,_position.y -20/SCALE_FACTOR);
		arr->removeObject(this);
	} 
	else
	{
		setPosition(_position.x,_position.y +20/SCALE_FACTOR);
		arr->addObject(this);
	}
	_isSelected = !_isSelected;
}

void Poke::unSelect()
{
	CCArray* arr = _gameMain->getArrPlayerOut();

	if (_isSelected)
	{
		setPosition(_position.x,_position.y -20/SCALE_FACTOR);
		arr->removeObject(this);
	}
	_isSelected = false;
}

void Poke::Select()
{
	CCArray* arr = _gameMain->getArrPlayerOut();

	if (!_isSelected)
	{
		setPosition(_position.x,_position.y +20/SCALE_FACTOR);
		arr->addObject(this);
	}
	_isSelected = true;
}