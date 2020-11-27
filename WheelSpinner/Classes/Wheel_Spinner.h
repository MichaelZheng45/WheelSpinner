#ifndef WHEEL_SPINNER_H
#define WHEEL_SPINNER_H

#include "cocos2d.h"
#include "Wheel_Slot.h"
#include <vector>

const int SPIN_TIMES = 3;
const float SHOW_REWARD_DURATION = 1;
const float REWARD_MOVE_IN_TIME = 0.5f;
const float SPIN_DURATION = 3;

class Wheel_Spinner
{
public:
	Wheel_Spinner();

	~Wheel_Spinner();

	void Init(Wheel_Slot sectors[], unsigned int slotCount,
		cocos2d::Sprite* wheelSprite, cocos2d::Sprite* wheelSpriteBorder, float spriteOffset, cocos2d::Vec2 labelOffset);

	void update(float delta);

	int spinWheel();

	std::tuple<Reward_Type, int> getReward(int sector);

	void animateWheel(int atSector);
	
	bool isSpinning() {return mWheelIsActive;}
private:
	std::vector<Wheel_Slot> mSectors;
	unsigned int mSlotCount;
	cocos2d::Sprite* mWheelSprite;
	cocos2d::Sprite* mWheelSpriteBorder;
	cocos2d::Sprite* mRewardSprite;
	cocos2d::Label* mRewardLabel;
	bool mWheelIsActive;

	float mCurrentDuration;
	float mAngleDiff;

};
#endif // !WHEEL_SPINNER_H

