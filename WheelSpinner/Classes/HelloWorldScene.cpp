/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include <iostream>
#include <fstream>
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

HelloWorld* HelloWorld::create() {
    HelloWorld* pRet = new HelloWorld();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /*
auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    } */

    //create spinner components

    Sprite* spinnerWheel = Sprite::create("wheel_sections_8.png");
    Sprite* spinnerBorder = Sprite::create("wheel_border.png");
    Sprite* arrow = Sprite::create("wheel_arrow.png");

    spinnerBorder->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(spinnerBorder);
    spinnerBorder->addChild(spinnerWheel);
    spinnerBorder->addChild(arrow);

    spinnerWheel->setPosition(Vec2(spinnerWheel->getContentSize().width / 2, spinnerWheel->getContentSize().height / 2));

    arrow->setPosition(Vec2(spinnerWheel->getContentSize().width/2, spinnerWheel->getContentSize().height / 2 + 450));

    Sprite* sprite0 = Sprite::create("heart.png");
    Wheel_Slot item0 = Wheel_Slot(sprite0, 20, Reward_Type::LIFE_REWARD, 30, "30min");

    Sprite* sprite1 = Sprite::create("brush.png");
    Wheel_Slot item1 = Wheel_Slot(sprite1, 10, Reward_Type::BRUSH_REWARD, 3, "x3");

    Sprite* sprite2 = Sprite::create("gem.png");
    Wheel_Slot item2 = Wheel_Slot(sprite2, 10, Reward_Type::GEMS_REWARD, 35, "x35");

    Sprite* sprite3 = Sprite::create("hammer.png");
    Wheel_Slot item3 = Wheel_Slot(sprite3, 10, Reward_Type::HAMMER_REWARD, 3, "x3");

    Sprite* sprite4 = Sprite::create("coin.png");
    Wheel_Slot item4 = Wheel_Slot(sprite4, 5, Reward_Type::COIN_REWARD, 750, "x750");

    Sprite* sprite5 = Sprite::create("brush.png");
    Wheel_Slot item5 = Wheel_Slot(sprite5,20, Reward_Type::BRUSH_REWARD, 1, "x1");

    Sprite* sprite6 = Sprite::create("gem.png");
    Wheel_Slot item6 = Wheel_Slot(sprite6, 5, Reward_Type::GEMS_REWARD, 75, "x75");

    Sprite* sprite7 = Sprite::create("hammer.png");
    Wheel_Slot item7 = Wheel_Slot(sprite7, 20, Reward_Type::HAMMER_REWARD, 1, "x1");

    Wheel_Slot slots[8] = { item0 ,item1 ,item2 ,item3 ,item4 ,item5 ,item6 ,item7 };

    Vec2 labelOffset = Vec2(120, 20);
    //create wheel Spinner
    mSpinner.Init(slots, 8, spinnerWheel, spinnerBorder, 300, labelOffset);

    //create button
    auto button = ui::Button::create("spin_button.png");
    button->setTitleText("Play On");
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 400));

    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            SpinWheel();
        }
    });

    this->addChild(button);

    //add keyboard listener for unit test
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::OnKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

    this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
    mSpinner.update(delta);
}


void HelloWorld::SpinWheel()
{
    if (!mSpinner.isSpinning())
    {
        int sector = mSpinner.spinWheel();

        //get the rewards
        std::tuple<Reward_Type, int> reward = mSpinner.getReward(sector);
        
        mSpinner.animateWheel(sector);
    }
}


void HelloWorld::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

    std::tuple<Reward_Type, int> reward;
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_0:
        mSpinner.animateWheel(0);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_1:
        mSpinner.animateWheel(1);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_2:
        mSpinner.animateWheel(2);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_3:
        mSpinner.animateWheel(3);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_4:
        mSpinner.animateWheel(4);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_5:
        mSpinner.animateWheel(5);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_6:
        mSpinner.animateWheel(6);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_7:
        mSpinner.animateWheel(7);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
        unitTest();
        break;
    default:
        break;
    }
}

void HelloWorld::unitTest()
{
    std::ofstream outFile;
    std::ofstream groupFile;

    outFile.open("TestRuns.txt");

    int groupResults[8] = {0,0,0,0,0,0,0,0};

    for (int i = 0; i < 1000; i++)
    {
        int sector = mSpinner.spinWheel();
        outFile << sector + '\n';

        groupResults[sector]++;
    }
    outFile.close();

    
    groupFile.open("GroupResults.txt");
    for (int i = 0; i < 8; i++)
    {
        groupFile << groupResults[i];
        groupFile << '\n';
    }

    groupFile.close();

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
