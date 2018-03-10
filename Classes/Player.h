#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Poke.h"
#include "SimpleAudioEngine.h"   //包含声音引擎头文件
#include "AppMacros.h"

USING_NS_CC;  
using namespace CocosDenshion;//使用该声音引擎的命名空间  

// 牌型
enum  CARD_TYPE
{
	SINGLE_CARD =1,			//单牌
	DOUBLE_CARD,			//对子
	THREE_CARD,				//3不带
	BOMB_CARD,				//炸弹
	MISSILE_CARD,			//火箭
	THREE_ONE_CARD,			//3带1
	THREE_TWO_CARD,			//3带2
	BOMB_TWO_CARD,			//四个带2张单牌
	BOMB_TWOOO_CARD,		//四个带2对
	CONNECT_CARD,			//连牌
	COMPANY_CARD,			//连队
	AIRCRAFT_CARD,			//飞机不带
	AIRCRAFT_SINGLE_CARD,	//飞机带单牌
	AIRCRAFT_DOUBLE_CARD,	//飞机带对子
	ERROR_CARD				//错误的牌型
};

// 每种牌的信息
struct CARDS_DATA
{
	std::vector<int>	_cards;
	CARD_TYPE			_type;
	unsigned int		_value;
};

// 出牌区

class PokeExhibitionZone : public cocos2d::Sprite
{

public:

	static PokeExhibitionZone* create()
	{
		PokeExhibitionZone *sprite = new (std::nothrow) PokeExhibitionZone();
		if (sprite && sprite->init())
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	virtual bool init()
	{
		// 初始化基类--------------------------------------------------------------
		if ( !Sprite::init() )
		{
			return false;
		}

		return true;
	}

	void chuPai(std::vector<PokeInfo> arrayIndexs)
	{
		if (arrayIndexs.empty())
		{
			auto label_buchu = cocos2d::Sprite::create("buchu.png");
			this->addChild(label_buchu);
		}

		//removeAllChildrenWithCleanup(true);

		//添加精灵
		for (int i=0; i<arrayIndexs.size(); ++i)
		{
			auto card = Poke::create(arrayIndexs.at(i));
			card->setScale(0.5);
			this->addChild(card, 100-arrayIndexs.at(i)._num);
		}

		sortAllChildren();

		int count = _children.size();
		for (int i=0; i<_children.size(); i++)
		{
			Poke* card = dynamic_cast<Poke*>(_children.at(i));
			if (card != NULL)
			{
				card->setPosition(i*30/SCALE_FACTOR, 0);
			}
		}
	}
};

class SceneGame;

//
// 玩家类
//

class Player : public cocos2d::Sprite
{
public:

	static Player* create(std::string name, int score, bool isHero);

    virtual bool init(std::string name, int score, bool isHero);

	void updateCards();
	void clearCards();

	// 地主信息
	void setDiZhu();
	bool getIsDiZhu() { return _isDiZhu; };

	// 出牌
	void FaPai(SceneGame* scene, PokeInfo info);
	void ChuPai(SceneGame* scene, bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value);
	void BuChu();
	void ChaiPai();

	void PlayEffectForCards(std::vector<int>& vec);

	void ShowTipInfo(bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value);

	bool IsQiangDiZhu();

	std::string GetName();
	void SetPlayerID(size_t id);
	size_t GetPlayerID();

	int GetScore();
	std::string GetScoreString();
	void Score(int delta_score);

	// 找跟牌的牌型
	std::vector<int>& FindFollowCards(CARD_TYPE cardType, unsigned int count, unsigned int value);
	// 找出牌的牌型
	std::vector<int>& FindOutCards();

	std::vector<PokeInfo>& GetOutCards();

protected:

	size_t	_id;
	bool	_isHero;
	bool	_isDiZhu;

	std::string	_name;
	int			_score;

	cocos2d::Sprite*_cardsManager;
	cocos2d::Label*	_labelName;
	cocos2d::Label*	_labelScore;
	cocos2d::Label*	_labelPokeCount;

	std::vector<PokeInfo>	_vecPokeInfo;

	std::vector<int>		_vecFindFollowCards;

	std::vector<PokeInfo>	_vecOutCards;	// 出牌存储区

	PokeExhibitionZone* _exhibitionZone;

	std::vector<CARDS_DATA>  _allCardGroups;

	cocos2d::Label*			_labelTipInfo; // 提示信息

	int m_intArray[15];          //记录每张牌出现的次数3----大鬼
};

#endif // __PLAYER_H__
