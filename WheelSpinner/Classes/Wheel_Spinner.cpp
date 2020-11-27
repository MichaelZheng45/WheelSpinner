#include "Wheel_Spinner.h"

Wheel_Spinner::Wheel_Spinner()
{

}

void Wheel_Spinner::Init(Wheel_Slot sectors[], unsigned int slotCount, cocos2d::Sprite* wheelSprite, cocos2d::Sprite* wheelSpriteBorder, float spriteOffset, cocos2d::Vec2 labelOffset)
{
	for (int i = 0; i < slotCount; i++)
	{
		mSectors.push_back(sectors[i]);
	}

	mSlotCount = slotCount;
	mWheelSprite = wheelSprite;
	mWheelSpriteBorder = wheelSpriteBorder;
	mWheelIsActive = false;
	mCurrentDuration = 0;

	//calulate angle between each sector
	 mAngleDiff = 360.0f/(float)mSlotCount;

	//starting from the top of the spinner and moving right, need to offset the angle by 90 degrees
	//find the angle for the first sector
	float initialAngle = 90.0f - mAngleDiff/2.0f;

	float toRadians = M_PI / 180;
	
	float sectorNumber = 0;
	for (std::vector<Wheel_Slot>::iterator it = mSectors.begin(); it != mSectors.end(); it++) 
	{
		//find the angle on the wheel for the given sector
		float targetAngle = initialAngle - mAngleDiff * sectorNumber;

		//get direction in vector form
		cocos2d::Vec2 direction = cocos2d::Vec2(cos(targetAngle * toRadians), sin(targetAngle * toRadians));

		//get final position
		cocos2d::Vec2 position = cocos2d::Vec2(wheelSprite->getContentSize().width/2.0f, wheelSprite->getContentSize().height/2.0f)  + direction * spriteOffset;
		
		//set position and rotation
		it->getRewardSprite()->setPosition(position);
		it->getRewardSprite()->setRotation(mAngleDiff / 2.0f + mAngleDiff * sectorNumber);

		//create label and set
		auto label = cocos2d::Label::createWithTTF(it->getLabelText(), "fonts/Marker Felt.ttf", 40);
		it->getRewardSprite()->addChild(label);
		label->setPosition(labelOffset);

		//set sector sprite as child to the wheel sprite
		mWheelSprite->addChild(it->getRewardSprite());
		sectorNumber++;
	}

	//create reward sprite and label
	mRewardSprite = cocos2d::Sprite::create();

	mRewardLabel = cocos2d::Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
	mRewardLabel->setPosition(labelOffset);
	mRewardSprite->setCascadeOpacityEnabled(true);
	mRewardSprite->addChild(mRewardLabel);

	mWheelSprite->addChild(mRewardSprite);
}

Wheel_Spinner::~Wheel_Spinner()
{

}

void Wheel_Spinner::update(float delta)
{
	if (mWheelIsActive)
	{
		mCurrentDuration +=delta;
		if (mCurrentDuration > SPIN_DURATION + SHOW_REWARD_DURATION)
		{
			mWheelIsActive = false;
		}			
	}
}

int Wheel_Spinner::spinWheel()
{
	//generate number 
	int dropNum = cocos2d::RandomHelper::random_int(0, 100);

	//value that compares with the drop number
	int dropValue = 0;
	int sector = 0;

	for (std::vector<Wheel_Slot>::iterator it = mSectors.begin(); it != mSectors.end(); it++)
	{
		//for every sector, check if it is in the drop threshold
		dropValue += it->getDropChance();
		if (dropValue >= dropNum)
		{
			return sector; 
		}
		sector++;
	}
	
	//error
	return -1;
}

std::tuple<Reward_Type, int> Wheel_Spinner::getReward(int sector)
{
	Reward_Type type = mSectors.at(sector).getReward();
	int rewardValue = mSectors.at(sector).getRewardValue();
	return std::tuple<Reward_Type, int> (type, rewardValue);
}

void Wheel_Spinner::animateWheel(int atSector)
{
	mWheelIsActive = true;
	mCurrentDuration = 0;

	//reset wheel
	mWheelSprite->setRotation(0);
	//calculate rotation 
	float targetAngle = -(mAngleDiff / 2.0f + mAngleDiff * atSector);

	//do fluid animation
	auto rotateBy= cocos2d::RotateBy::create(SPIN_DURATION, targetAngle + SPIN_TIMES * 360);
	auto easeInOutBack = cocos2d::EaseBackInOut::create(rotateBy->clone());
	mWheelSprite->runAction(easeInOutBack);

	//set sprite texture that will pop up after spin finishes sequence
	mRewardSprite->setSpriteFrame(mSectors.at(atSector).getRewardSprite()->getSpriteFrame());
	mRewardSprite->setOpacity(0);
	
	//get the position at the center of the wheel
	cocos2d::Vec2 centerPosition = cocos2d::Vec2(mWheelSprite->getContentSize().width / 2, mWheelSprite->getContentSize().height / 2);

	//set label text
	mRewardLabel->setString(mSectors.at(atSector).getLabelText());

	//set position and rotation
	mRewardSprite->setPosition(centerPosition +  cocos2d::Vec2(cos((targetAngle + 90) * (M_PI / 180)), sin((targetAngle + 90) * (M_PI / 180))) * 200);
	mRewardSprite->setRotation(-targetAngle);

	//create actions for the reward to follow
	auto spawn = cocos2d::Spawn::createWithTwoActions(cocos2d::FadeTo::create(REWARD_MOVE_IN_TIME, 255)
													, cocos2d::MoveTo::create(REWARD_MOVE_IN_TIME, centerPosition));
	auto fadeOut = cocos2d::FadeTo::create(REWARD_MOVE_IN_TIME, 0);

	auto showDelay = cocos2d::DelayTime::create(SPIN_DURATION);
	auto waitDelay = cocos2d::DelayTime::create(SHOW_REWARD_DURATION - REWARD_MOVE_IN_TIME);
	
	auto sequence = cocos2d::Sequence::create(showDelay, spawn, waitDelay, fadeOut, nullptr);
	mRewardSprite->runAction(sequence);
}