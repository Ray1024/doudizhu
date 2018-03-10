#include "AppCommon.h"
#include "Poke.h"

USING_NS_CC;

MenuItemSprite* customMenuItem(const std::string& normalImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
	auto image = Sprite::create(normalImage);
	image->setColor(Color3B(100,100,100));
	auto item = MenuItemSprite::create(
		Sprite::create(normalImage),
		image,
		Sprite::create(disabledImage),
		callback);

	return item;
}

MenuItemSprite* customMenuItemWithSpriteFrameName(const std::string& normalImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
	auto image = Sprite::createWithSpriteFrameName(normalImage);
	image->setColor(Color3B(100,100,100));
	auto item = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName(normalImage),
		image,
		Sprite::createWithSpriteFrameName(disabledImage),
		callback);

	return item;
}

// 判断是否连续

bool IsContinuous(std::vector<int>& vec)
{
	bool ret = true;

	// 排序
	std::sort(vec.begin(), vec.end());

	// 排序完成后比较相邻的两个数字的差值，如果全为1，则为连续
	for (int i=0; i<vec.size()-1; i++)
	{
		if (vec[i+1] - vec[i] != 1)
		{
			ret = false;
			break;
		}
	}

	return ret;
}

bool IsContinuous(CCArray* vecPoke)
{
	unsigned int length = vecPoke->count();
	std::vector<int> vec;

	for (int i=0; i<length; i++)
	{
		Poke* poke = dynamic_cast<Poke*>(vecPoke->objectAtIndex(i));
		if (poke != NULL)
		{
			vec.push_back(poke->_info._num);
		}
	}

	return IsContinuous(vec);
}

// 判断是否都小于2
bool IsLessTwo(CCArray* vecPoke)
{
	bool ret = false;

	unsigned int length = vecPoke->count();
	for (int i=0; i<length; i++)
	{
		Poke* poke = dynamic_cast<Poke*>(vecPoke->objectAtIndex(i));
		if (poke != NULL)
		{
			ret = poke->_info._num >= 12;
		}
	}

	return !ret;
}

bool IsLessTwo(std::vector<int>& vecPoke)
{
	bool ret = false;

	for (int i=0; i<vecPoke.size(); i++)
	{
		ret = vecPoke[i] >= 12;
	}

	return !ret;
}

struct CRAD_INDEX
{
	std::vector<int>	single_index;	//记录单张的牌
	std::vector<int>	double_index;	//记录对子的牌
	std::vector<int>	three_index;	//记录3张
	std::vector<int>	four_index;		//记录4张
};

CARDS_DATA PanDuanPaiXing(CCArray* cards)
{
	std::vector<int> vec;
	for (int i=0; i<cards->count(); i++)
	{
		Poke* poke = dynamic_cast<Poke*>(cards->objectAtIndex(i));
		if (poke != NULL)
		{
			vec.push_back(poke->_info._num);
		}
	}

	return PanDuanPaiXing(vec);
}

CARDS_DATA PanDuanPaiXing(std::vector<PokeInfo>& cards)
{
	std::vector<int> vec;
	for (int i=0; i<cards.size(); i++)
	{
		vec.push_back(cards[i]._num);
	}

	return PanDuanPaiXing(vec);
}

CARDS_DATA PanDuanPaiXing(std::vector<int>& cards)
{
	CARDS_DATA ret;
	unsigned int length = cards.size();
	std::sort(cards.begin(), cards.end());

	for (int i = 0; i < length; i++)
	{
		ret._cards.push_back(cards[i]);
	}

	//小于5张牌
	//单牌，对子，3不带,炸弹通用算法
	if(length > 0 && length < 5) 
	{
		// 单牌/对子/三不带/炸弹
		if(cards[0] == cards[length - 1])
		{
			ret._type = (CARD_TYPE)length;
			if (length == 4)
			{
				ret._value = 100 + cards[0];
			}
			else
			{
				ret._value = (length - 1)*20 + cards[0];
			}
			return ret;
		}

		// 火箭
		if (cards[0] == NUM_XW && cards[1] == NUM_DW && length == 2)
		{
			ret._type = MISSILE_CARD;
			ret._value = 120;
			return ret;
		}

		// 三带一
		if ((cards[0] == cards[length - 2] && length == 4)
			|| (cards[1] == cards[length - 1] && length == 4))
		{
			ret._type = THREE_ONE_CARD;
			if ((cards[0] == cards[length - 2] && length == 4))
			{
				ret._value = 40 + cards[0];
			}
			else
			{
				ret._value = 40 + cards[1];
			}

			return ret;
		}
	}

	// 大于等于5张牌
	else if (length >= 5)
	{
		// 连牌
		if (IsContinuous(cards) && IsLessTwo(cards))
		{
			ret._type = CONNECT_CARD;
			ret._value = 60 + cards[0];
			return ret;
		}

		// 连对
		if (length >= 6 && length % 2 == 0) // 判断是否大于六张，且为双数
		{
			// 判断是否都是对子
			bool is_all_double = true;

			for (int i=0; i<length; i+=2)
			{
				if (cards[i] != cards[i+1])
				{
					is_all_double = false;
					break;
				}
			}

			// 判断对子是否连续
			if (is_all_double)
			{
				std::vector<int> vec_single;
				for (int i=0; i<length; i+=2)
				{
					vec_single.push_back(cards[i]);
				}

				if (IsContinuous(vec_single))
				{
					ret._type = COMPANY_CARD;
					ret._value = 80 + cards[0];
					return ret;
				}
			}
		}

		// 将数组中的牌数分到结构体CRAD_INDEX中
		CRAD_INDEX card_index;

		for (int i=0; i<length; )
		{
			if (i+1 < length && cards[i] == cards[i+1])
			{
				if (i+2 < length && cards[i+1] == cards[i+2])
				{
					if (i+3 < length && cards[i+2] == cards[i+3])
					{
						card_index.four_index.push_back(cards[i]);
						i += 4;
					}
					else
					{
						card_index.three_index.push_back(cards[i]);
						i += 3;
					}
				}
				else
				{
					card_index.double_index.push_back(cards[i]);
					i += 2;
				}
			}
			else
			{
				card_index.single_index.push_back(cards[i]);
				i++;
			}
		}

		// 3带对
		if (card_index.three_index.size() == 1 && card_index.double_index.size() == 1 && card_index.four_index.empty() && card_index.single_index.empty())
		{
			ret._type = THREE_TWO_CARD;
			ret._value = 40 + card_index.three_index[0];
			return ret;
		}

		// 飞机
		// 前提：两个连续三张的
		if (card_index.four_index.empty() && card_index.three_index.size() == 2 && card_index.three_index[0] + 1 == card_index.three_index[1])
		{
			// 333444
			if (card_index.single_index.empty() && card_index.double_index.empty())
			{
				ret._type = AIRCRAFT_CARD;
				ret._value = 80 + cards[0];
				return ret;
			}

			// 33344456
			if (card_index.double_index.empty() && card_index.single_index.size() == 2)
			{
				ret._type = AIRCRAFT_SINGLE_CARD;
				ret._value = 80 + cards[0];
				return ret;
			}

			// 33344455
			if (card_index.single_index.empty() && card_index.double_index.size() == 1)
			{
				ret._type = AIRCRAFT_SINGLE_CARD;
				ret._value = 80 + cards[0];
				return ret;
			}

			// 3334445566
			if (card_index.single_index.empty() && card_index.double_index.size() == 2)
			{
				ret._type = AIRCRAFT_DOUBLE_CARD;
				ret._value = 80 + cards[0];
				return ret;
			}
		}

		// 4带2
		if (card_index.four_index.size() == 1 && length % 2 == 0 && card_index.three_index.empty())
		{

			// 444423
			if (card_index.single_index.size() == 2 && card_index.double_index.empty())
			{
				ret._type = BOMB_TWO_CARD;
				ret._value = 100 + cards[0];
				return ret;
			}

			// 444422
			if (card_index.double_index.size() == 1 && card_index.single_index.empty())
			{
				ret._type = BOMB_TWO_CARD;
				ret._value = 80 + cards[0];
				return ret;
			}

			// 44442233
			if (card_index.double_index.size() == 2 && card_index.single_index.empty())
			{
				ret._type = BOMB_TWOOO_CARD;
				ret._value = 80 + cards[0];
				return ret;
			}
		}
	}

	ret._type = ERROR_CARD;
	ret._value = 0;
	return ret;
}