
#include "Wheel_Slot.h"

Wheel_Slot::Wheel_Slot(cocos2d::Sprite* rewardSprite, unsigned int dropChance, Reward_Type reward, int rewardValue, std::string labelText)
{
	mRewardSprite = rewardSprite;
	mDropChance = dropChance;
	mReward = reward;
	mRewardValue = rewardValue;
	mLabelText = labelText;
}

Wheel_Slot::~Wheel_Slot()
{
}

