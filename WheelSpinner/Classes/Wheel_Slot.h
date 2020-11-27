#ifndef WHEEL_SLOT_H
#define WHEEL_SLOT_H

#include "cocos2d.h"

enum class Reward_Type
{
	INVALID_REWARD = -1,
	LIFE_REWARD,
	BRUSH_REWARD,
	GEMS_REWARD,
	HAMMER_REWARD,
	COIN_REWARD
};

class Wheel_Slot
{
public:
	Wheel_Slot(cocos2d::Sprite* rewardSprite, unsigned int dropChance, Reward_Type reward, int rewardValue, std::string labelText);
	~Wheel_Slot();

	cocos2d::Sprite* getRewardSprite() {return mRewardSprite;}
	int getDropChance() {return mDropChance;}
	Reward_Type getReward() {return mReward;}
	int getRewardValue() {return mRewardValue; }
	std::string getLabelText() {return mLabelText; }

private:
	cocos2d::Sprite* mRewardSprite;
	unsigned int mDropChance;
	int mRewardValue;
	Reward_Type mReward;
	std::string mLabelText;
};


#endif // !WHEEL_SLOT_H
