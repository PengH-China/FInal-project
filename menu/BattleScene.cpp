/**
*@file BattleScene.cpp
*@author ÕÅ×Óº­
*@date 6/1/2021
*/


#include "cocos2d.h"
#include "BattleScene.h"

using namespace cocos2d;

cocos2d::Scene* BattleScene::createScene()
{
	return BattleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//±³¾°Í¼Æ¬ background picture
	BattleScene::loadBackgroundPicture(this);

	return true;
}

void BattleScene::loadBackgroundPicture(cocos2d::Ref* pSender)
{
	//c
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Background MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* menuBackground = Sprite::create("background.jpg");
	menuBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	

	this->addChild(menuBackground);
}



void BattleScene::menuBackCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch back MenuItem %p", item);

	Director::getInstance()->popScene();

}

