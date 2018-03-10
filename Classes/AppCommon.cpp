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

// �ж��Ƿ�����

bool IsContinuous(std::vector<int>& vec)
{
	bool ret = true;

	// ����
	std::sort(vec.begin(), vec.end());

	// ������ɺ�Ƚ����ڵ��������ֵĲ�ֵ�����ȫΪ1����Ϊ����
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

// �ж��Ƿ�С��2
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
	std::vector<int>	single_index;	//��¼���ŵ���
	std::vector<int>	double_index;	//��¼���ӵ���
	std::vector<int>	three_index;	//��¼3��
	std::vector<int>	four_index;		//��¼4��
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

	//С��5����
	//���ƣ����ӣ�3����,ը��ͨ���㷨
	if(length > 0 && length < 5) 
	{
		// ����/����/������/ը��
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

		// ���
		if (cards[0] == NUM_XW && cards[1] == NUM_DW && length == 2)
		{
			ret._type = MISSILE_CARD;
			ret._value = 120;
			return ret;
		}

		// ����һ
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

	// ���ڵ���5����
	else if (length >= 5)
	{
		// ����
		if (IsContinuous(cards) && IsLessTwo(cards))
		{
			ret._type = CONNECT_CARD;
			ret._value = 60 + cards[0];
			return ret;
		}

		// ����
		if (length >= 6 && length % 2 == 0) // �ж��Ƿ�������ţ���Ϊ˫��
		{
			// �ж��Ƿ��Ƕ���
			bool is_all_double = true;

			for (int i=0; i<length; i+=2)
			{
				if (cards[i] != cards[i+1])
				{
					is_all_double = false;
					break;
				}
			}

			// �ж϶����Ƿ�����
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

		// �������е������ֵ��ṹ��CRAD_INDEX��
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

		// 3����
		if (card_index.three_index.size() == 1 && card_index.double_index.size() == 1 && card_index.four_index.empty() && card_index.single_index.empty())
		{
			ret._type = THREE_TWO_CARD;
			ret._value = 40 + card_index.three_index[0];
			return ret;
		}

		// �ɻ�
		// ǰ�᣺�����������ŵ�
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

		// 4��2
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